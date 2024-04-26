#include "lumen/web/server.hpp"

#include "lumen/web/error.hpp"
#include "lumen/web/handler/advertisement.hpp"
#include "lumen/web/handler/common.hpp"
#include "lumen/web/handler/event.hpp"
#include "lumen/web/handler/football.hpp"
#include "lumen/web/handler/soccer.hpp"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace lumen::web {
namespace {

constexpr auto tag = "web/server";

// Not the best, but I'm not of a better option that doesn't make the variable
// visible outside of this file.
int g_event_stream_socket{};

SemaphoreHandle_t event_stream_semaphore{};
QueueHandle_t event_stream_queue{};

/// Initialize all structures required for the event stream task.
void start_event_stream_task();

/** Register all of the endpoints.
 *
 * \param server A reference to a valid http server handle.
 *
 * \param context A reference to a Context object.
 */
void register_endpoints(httpd_handle_t& server);

/** The handler that's called before a socket is closed.
 *
 * \param handle The instance of the server.
 *
 * \param socket_fd The session socket file descriptor.
 */
void on_close(httpd_handle_t handle, int socket_fd);

/** Asynchronous handler for long-running event-stream requests.
 *
 * \param parameters Unused, but required for FreeRTOS tasks.
 */
void event_stream_task(void* parameters);

} // namespace

Server::Server(activity::Context& activity_context)
    : activity_context_{&activity_context}
{
    ESP_LOGI(tag, "Starting web server");

    start_event_stream_task();

    config_.stack_size = 8192;
    config_.max_uri_handlers = 16;
    config_.global_user_ctx = this;
    config_.uri_match_fn = httpd_uri_match_wildcard;

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

void send_event_message(EventMessage const& message)
{
    // Send message if the event stream is running
    if (uxSemaphoreGetCount(event_stream_semaphore) == 0) {
        xQueueSend(event_stream_queue, &message, 0);
    }
}

esp_err_t dispatch_event_handler(httpd_req_t* request)
{
    httpd_req_t* copy = nullptr;

    auto error = httpd_req_async_handler_begin(request, &copy);

    if (error != ESP_OK) {
        return error;
    }

    auto handler_message =
        EventMessage{EventMessage::Type::event_stream_started, copy};

    if (xSemaphoreTake(event_stream_semaphore, 0) == pdFALSE) {
        ESP_LOGE(tag, "No workers are available");
        httpd_req_async_handler_complete(copy); // cleanup
        return ESP_FAIL;
    }

    if (xQueueSend(event_stream_queue, &handler_message, 0) == pdFALSE) {
        ESP_LOGE(tag, "worker queue is full");
        httpd_req_async_handler_complete(copy); // cleanup
        return ESP_FAIL;
    }

    auto* server =
        static_cast<Server*>(httpd_get_global_user_ctx(request->handle));

    g_event_stream_socket = httpd_req_to_sockfd(copy);

    return ESP_OK;
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

    httpd_uri_t soccer_get_uri = {
        .uri = "/api/v1/soccer",
        .method = HTTP_GET,
        .handler = handler::soccer_get,
        .user_ctx = nullptr
    };

    httpd_uri_t soccer_put_uri = {
        .uri = "/api/v1/soccer",
        .method = HTTP_PUT,
        .handler = handler::soccer_put,
        .user_ctx = nullptr
    };

    httpd_uri_t advertisement_get_uri = {
        .uri = "/api/v1/advertisement",
        .method = HTTP_GET,
        .handler = handler::advertisement_get,
        .user_ctx = nullptr
    };

    httpd_uri_t advertisement_post_uri = {
        .uri = "/api/v1/advertisement",
        .method = HTTP_POST,
        .handler = handler::advertisement_post,
        .user_ctx = nullptr
    };

    httpd_uri_t advertisement_delete_uri = {
        .uri = "/api/v1/advertisement",
        .method = HTTP_DELETE,
        .handler = handler::advertisement_delete,
        .user_ctx = nullptr
    };

    httpd_uri_t common_get_uri = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = handler::common_get,
        .user_ctx = nullptr
    };

    httpd_register_uri_handler(server, &event_get_uri);
    httpd_register_uri_handler(server, &football_get_uri);
    httpd_register_uri_handler(server, &football_put_uri);
    httpd_register_uri_handler(server, &soccer_get_uri);
    httpd_register_uri_handler(server, &soccer_put_uri);
    httpd_register_uri_handler(server, &advertisement_get_uri);
    httpd_register_uri_handler(server, &advertisement_post_uri);
    httpd_register_uri_handler(server, &advertisement_delete_uri);
    httpd_register_uri_handler(server, &common_get_uri);
}

void on_close(httpd_handle_t handle, int socket_fd)
{
    auto* server = static_cast<Server*>(httpd_get_global_user_ctx(handle));

    if (socket_fd == g_event_stream_socket) {
        send_event_message(EventMessage{EventMessage::Type::event_stream_closed}
        );
    }

    close(socket_fd);
}

/// TODO: Have an array of 5 event stream tasks instead of a single one.
/// HTTP 1.1 is limited to 6 concurrent TCP connections, so we could have 5
/// tasks available (up to 5 browser tabs), and leave one TCP connection
/// available for synchronous requests.
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

                g_event_stream_socket = 0;

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
                ESP_LOGI(tag, "SENDING EVENT STREAM MESSAGE");

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
