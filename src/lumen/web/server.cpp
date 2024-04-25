#include "lumen/web/server.hpp"

#include "lumen/web/error.hpp"
#include "lumen/web/handler/common.hpp"
#include "lumen/web/handler/football.hpp"

#include "esp_http_server.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include <cstring> // strcmp

using json = nlohmann::json;

namespace lumen::web {
namespace {

constexpr auto tag = "web/server";

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

esp_err_t event_get_handler(httpd_req_t* request);
void event_handler_task(void* parameters);

} // namespace

Server::Server(activity::Context& activity_context)
    : activity_context_{&activity_context}
{
    ESP_LOGI(tag, "Starting web server");

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

namespace {

esp_err_t dispatch_event_handler(httpd_req_t* request)
{
    // Get the socketfd from the session ctx
    return ESP_OK;
}

esp_err_t event_get_handler(httpd_req_t* request)
{
    ESP_LOGI(tag, "uri: /api/v1/event");

    auto header_len = httpd_req_get_hdr_value_len(request, "Accept");
    char buffer[header_len + 1] = {0};

    httpd_req_get_hdr_value_str(request, "Accept", buffer, header_len + 1);

    if (strcmp(buffer, "text/event-stream") != 0) {
        ESP_LOGI(tag, "Accept: %s", buffer);
        return send_error(
            request, 400, "Accept header is not \"text/event-stream\"."
        );
    }

    httpd_resp_set_type(request, "text/event-stream");

    // Check if there is an available event handler task

    // if (dispatch_event_handler(request) == ESP_OK) {
    if (false) {
        return ESP_OK;
    } else {
        return send_error(
            request, 503, "No event-handler threads are available."
        );
    }
}

void register_endpoints(httpd_handle_t& server)
{

    httpd_uri_t event_get_uri = {
        .uri = "/api/v1/event",
        .method = HTTP_GET,
        .handler = event_get_handler,
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
    ESP_LOGI(tag, "Server socket opened: %d", socket_fd);

    auto* server = static_cast<Server*>(httpd_get_global_user_ctx(handle));

    // Save socket fd in session context
    // httpd_sess_set_ctx(handle, sockfd, server->add_session(sockfd), [](void*)
    // {
    //});

    auto* activity_context = server->get_activity_context();

    // The connect activity is over when the user opens the website.
    // Restore the previous activity.
    if (activity_context->get_activity_type() == activity::Type::connect) {
        activity_context->restore_activity();
    }

    return ESP_OK;
}

void on_close(httpd_handle_t server, int sockfd)
{
    ESP_LOGI(tag, "Server socket closed: %d", sockfd);
    close(sockfd);
}

void event_handler_task(void* /* parameters */)
{
    // ESP_LOGI(tag, "Starting event handler task");

    //// We need to get the request pointer, from which we can receive a context
    //// pointer

    // auto context;

    // while (true) {
    //     if (xQueueReceive(event_handler_queue, &event_data, portMAX_DELAY)) {
    //         ESP_LOGI(tag, "Sending event");
    //     }

    //    auto dump = context->to_json().dump();

    //    auto ret = httpd_resp_send_chunk(request, dump.c_str(), dump.size());

    //    if (ret != ESP_OK) {
    //        ESP_LOGW(tag, "Error in sending event data");

    //    }

    //}
}

} // namespace

} // namespace lumen::web
