#include "lumen/web/server.hpp"

#include "lumen/web/handler/common.hpp"
#include "lumen/web/handler/football.hpp"

#include "esp_http_server.h"
#include "esp_log.h"

#include "freertos/task.h"

namespace lumen::web {
namespace {

constexpr auto tag = "web/server";

/** Register all of the endpoints.
 *
 * \param server A reference to a valid http server handle.
 *
 * \param context A reference to a Context object.
 */
void register_endpoints(httpd_handle_t& server, activity::Context& context);

/** The handler for a new socket connection.
 *
 * \param handle The instance of the server.
 *
 * \param socket_fd The session socket file descriptor.
 *
 * \returns `ESP_OK` on success.
 */
esp_err_t on_open(httpd_handle_t handle, int socket_fd);

} // namespace

Server::Server(activity::Context& context)
{
    ESP_LOGI(tag, "Starting web server");

    config.stack_size = 8192;

    config.global_user_ctx = &context;
    config.open_fn = on_open;

    config.uri_match_fn = httpd_uri_match_wildcard;

    httpd_start(&server, &config);
    register_endpoints(server, context);

    ESP_LOGI(tag, "Web server started");
}

Server::~Server()
{
    ESP_LOGI(tag, "Stopping web server");
    httpd_stop(server);
}

namespace {

void register_endpoints(httpd_handle_t& server, activity::Context& context)
{
    httpd_uri_t football_put_uri = {
        .uri = "/api/v1/football",
        .method = HTTP_PUT,
        .handler = handler::football_put,
        .user_ctx = &context
    };

    httpd_uri_t common_get_uri = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = handler::common_get,
        .user_ctx = &context
    };

    httpd_register_uri_handler(server, &football_put_uri);
    httpd_register_uri_handler(server, &common_get_uri);
}

esp_err_t on_open(httpd_handle_t handle, int /* socket_fd */)
{
    auto* activity_context =
        static_cast<activity::Context*>(httpd_get_global_user_ctx(handle));

    // The connect activity is over when the user opens the website.
    // Restore the previous activity.
    if (activity_context->get_activity_type() == activity::Type::connect) {
        activity_context->restore_activity();
    }

    return ESP_OK;
}

} // namespace

} // namespace lumen::web
