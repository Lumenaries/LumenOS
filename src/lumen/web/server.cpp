#include "lumen/web/server.hpp"

#include "lumen/web/error.hpp"
#include "lumen/web/handler/common.hpp"
#include "lumen/web/handler/event.hpp"
#include "lumen/web/handler/football.hpp"

#include "esp_http_server.h"
#include "esp_log.h"

using json = nlohmann::json;

namespace lumen::web {
namespace {

constexpr auto tag = "web/server";

void start_event_stream_task();

/** Register all of the endpoints.
 *
 * \param server A reference to a valid http server handle.
 *
 * \param context A reference to a Context object.
 */
void register_endpoints(httpd_handle_t& server);

/** The handler for a new socket connection.
 *
 * \param handle The instance of the server.
 *
 * \param socket_fd The session socket file descriptor.
 *
 * \returns `ESP_OK` on success.
 */
esp_err_t on_open(httpd_handle_t handle, int socket_fd);
void on_close(httpd_handle_t handle, int socket_fd);

/// TODO: Have an array of 5 event stream tasks instead of a single one.
/// HTTP 1.1 is limited to 6 concurrent TCP connections, so we could have 5
/// tasks available (up to 5 browser tabs), and leave one TCP connection
/// available for synchronous requests.
void event_stream_task(void* parameters);

} // namespace

Server::Server(activity::Context& activity_context)
    : activity_context_{&activity_context}
{
    ESP_LOGI(tag, "Starting web server");

    start_event_stream_task();

    config_.stack_size = 8192;
    config_.global_user_ctx = this;
    config_.uri_match_fn = httpd_uri_match_wildcard;

    config_.open_fn = on_open;
    config_.close_fn = on_close;

    httpd_start(&handle_, &config_);
    register_endpoints(handle_);
}

Server::~Server()
{
    ESP_LOGI(tag, "Stopping web server");
    httpd_stop(handle_);
}

activity::Context* Server::get_activity_context() const
{
    return activity_context_;
}

void Server::send_event_message(EventMessage const& message)
{
    // Send message if the event stream is running
    if (uxSemaphoreGetCount(event_stream_semaphore) == 0) {
        xQueueSend(event_stream_queue, &message, 0);
    }
}

void Server::set_event_stream_socket(int socket_fd)
{
    event_socket_fd_ = socket_fd;
}

int Server::get_event_stream_socket() const
{
    return event_socket_fd_;
}

esp_err_t Server::set_event_stream(httpd_req_t* request)
{
    if (event_stream_ == nullptr) {
        return ESP_FAIL;
    }

    event_stream_ = std::make_unique<event::Stream>(request);
}

namespace {

void register_endpoints(httpd_handle_t& server)
{

    httpd_uri_t event_get_uri = {
        .uri = "/api/v1/event",
        .method = HTTP_GET,
        .handler = handler::event_get,
        .user_ctx = nullptr
    };

    httpd_uri_t football_get_uri = {
        .uri = "/api/v1/football",
        .method = HTTP_GET,
        .handler = handler::football_get,
        .user_ctx = nullptr
    };

    httpd_uri_t football_put_uri = {
        .uri = "/api/v1/football",
        .method = HTTP_PUT,
        .handler = handler::football_put,
        .user_ctx = nullptr
    };

    // This needs to be the last GET handler
    httpd_uri_t common_get_uri = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = handler::common_get,
        .user_ctx = nullptr
    };

    httpd_register_uri_handler(server, &event_get_uri);
    httpd_register_uri_handler(server, &football_get_uri);
    httpd_register_uri_handler(server, &football_put_uri);
    httpd_register_uri_handler(server, &common_get_uri);
}

esp_err_t on_open(httpd_handle_t handle, int socket_fd)
{
    auto* activity_context =
        static_cast<Server*>(httpd_get_global_user_ctx(handle))
            ->get_activity_context();

    // The connect activity is over when the user opens the website.
    // Restore the previous activity.
    if (activity_context->get_activity_type() == activity::Type::connect) {
        activity_context->restore_activity();
    }

    return ESP_OK;
}

void on_close(httpd_handle_t handle, int socket_fd)
{
    auto* event_stream = static_cast<Server*>(httpd_get_global_user_ctx(handle))
                             ->get_event_stream();

    if (socket_fd == event_stream->get_socket()) {
        server->close_event_stream();
    }

    if (socket_fd == server->get_event_stream_socket()) {
        server->send_event_message(
            EventMessage{EventMessage::Type::event_stream_closed}
        );
    }

    close(socket_fd);
}

void event_stream_task(void* /* parameters */)
{
    EventMessage message{};
    httpd_req_t* event_stream{};

    while (true) {
        xQueueReceive(event_stream_queue, &message, portMAX_DELAY);

        if (message.type == EventMessage::Type::event_stream_closed) {
            if (event_stream != nullptr) {
                auto* server = static_cast<Server*>(
                    httpd_get_global_user_ctx(event_stream->handle)
                );

                server->set_event_stream_socket(0);

                httpd_req_async_handler_complete(event_stream);

                event_stream = nullptr;

                // Signal that we're ready to receive a new event stream
                xSemaphoreGive(event_stream_semaphore);
            }

        } else if (message.type == EventMessage::Type::event_stream_started) {
            if (message.new_request != nullptr) {
                event_stream = message.new_request;
            }

        } else if (message.type == EventMessage::Type::event_occurred) {
            if (event_stream != nullptr) {

                auto* activity_context =
                    static_cast<Server*>(
                        httpd_get_global_user_ctx(event_stream->handle)
                    )
                        ->get_activity_context();

                /// TODO: Only send the values that have changed. This can be
                /// done by adding a "has_changed" flag to each field and
                /// creating a "get_change_json()" on the context that will
                /// compile all modified values into a json object. This could
                /// also be used to reduce display flashing when updating.
                auto data =
                    "data:" + activity_context->get_activity_json().dump() +
                    "\n\n";

                httpd_resp_send_chunk(
                    event_stream, data.c_str(), HTTPD_RESP_USE_STRLEN
                );
            }
        }
    }
}

void start_event_stream_task()
{
    // Create semaphore
    event_stream_semaphore = xSemaphoreCreateBinary();
    if (event_stream_semaphore == nullptr) {
        ESP_LOGE(tag, "Failed to create semaphore");
        return;
    }

    xSemaphoreGive(event_stream_semaphore);

    // Create queue
    event_stream_queue = xQueueCreate(1, sizeof(EventMessage));
    if (event_stream_queue == nullptr) {
        ESP_LOGE(tag, "Failed to create event_stream_queue");
        vSemaphoreDelete(event_stream_semaphore);
        return;
    }

    // Start worker task
    auto success = xTaskCreate(
        event_stream_task, "Event Stream Task", 8192, nullptr, 5, nullptr
    );

    if (success == pdFALSE) {
        ESP_LOGE(tag, "Failed to start event stream task");
    }
}

} // namespace

} // namespace lumen::web
