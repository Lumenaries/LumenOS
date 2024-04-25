#include "lumen/web/server.hpp"

#include "lumen/web/error.hpp"

#include "esp_log.h"
#include "esp_vfs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include <cstring> // strcmp
#include <fcntl.h>
#include <string>

using json = nlohmann::json;

namespace lumen::web {
namespace {

constexpr auto tag = "web/server";

constexpr auto chunk_buffer_size = 10240;
char chunk[chunk_buffer_size];

/** Register all of the endpoints.
 *
 * \param server A reference to a valid http server handle.
 *
 * \param context A reference to a Context object.
 */
void register_endpoints(httpd_handle_t& server, activity::Context& context);

esp_err_t event_get_handler(httpd_req_t* request);
void event_handler_task(void* parameters);

esp_err_t on_open(httpd_handle_t hd, int sockfd);
void on_close(httpd_handle_t hd, int sockfd);

} // namespace

Server::Server(activity::Context& context)
{
    ESP_LOGI(tag, "Starting web server");

    config.uri_match_fn = httpd_uri_match_wildcard;
    config.open_fn = on_open;
    config.close_fn = on_close;

    httpd_start(&server, &config);
    register_endpoints(server, context);
}

Server::~Server()
{
    ESP_LOGI(tag, "Stopping web server");
    httpd_stop(server);
}

namespace {

/* Compare the extension of the filepath with a given extension.
 *
 * \param filepath The path to the file.
 * \param ext The extension to compare the file to.
 *
 * \returns true if the filepath extension matches the given extension.
 * \returns false if the filepath extension does not match the given extension.
 */
bool check_file_extension(char const* filepath, char const* ext)
{
    char const* dot = strrchr(filepath, '.');

    if (dot == nullptr && dot == ext) {
        return true;
    }

    if (dot != nullptr && ext != nullptr && strcmp(dot, ext) == 0) {
        return true;
    }

    return false;
}

/** Set the type of the response based on the file extension.
 *
 * \param req Pointer to the request being handled.
 * \param filepath The path to the file to be opened.
 */
esp_err_t set_content_type_from_file(httpd_req_t* req, char const* filepath)
{
    const char* type = "text/plain";

    if (check_file_extension(filepath, ".html")) {
        type = "text/html";
    } else if (check_file_extension(filepath, ".js")) {
        type = "application/javascript";
    } else if (check_file_extension(filepath, ".css")) {
        type = "text/css";
    } else if (check_file_extension(filepath, ".png")) {
        type = "image/png";
    } else if (check_file_extension(filepath, ".ico")) {
        type = "image/x-icon";
    } else if (check_file_extension(filepath, ".svg")) {
        type = "image/svg+xml";
    }

    return httpd_resp_set_type(req, type);
}

/** The default GET handler.
 *
 * \param req Pointer to the request being handled.
 */
esp_err_t common_get_handler(httpd_req_t* req)
{
    uint32_t filepath_max = ESP_VFS_PATH_MAX + 128;
    char filepath[filepath_max] = "/www";

    // If the user navigates to the root or to the a client-side route (a route
    // that has no file extension), send the index.html.
    // TODO: If request is not root and doesn't have a file extension, check to
    // see if that file exists in the filesystem before assuming that it's a
    // client-side route.
    if (req->uri[strlen(req->uri) - 1] == '/' ||
        check_file_extension(req->uri, nullptr)) {
        strlcat(filepath, "/index.html", sizeof(filepath));
    } else {
        strlcat(filepath, req->uri, sizeof(filepath));
    }

    int fd = open(filepath, O_RDONLY, 0);
    if (fd == -1) {
        ESP_LOGE(tag, "Failed to open file : %s", filepath);

        send_error(req, 500, "Failed to read existing file");
        return ESP_FAIL;
    }

    set_content_type_from_file(req, filepath);

    ssize_t read_bytes;

    do {
        // Read the file in the scratch buffer in chunks
        read_bytes = read(fd, chunk, chunk_buffer_size);

        if (read_bytes == -1) {
            ESP_LOGE(tag, "Failed to read file : %s", filepath);
        } else if (read_bytes > 0) {
            // Send the buffer contents as HTTP response chunk
            if (httpd_resp_send_chunk(req, chunk, read_bytes) != ESP_OK) {
                close(fd);
                ESP_LOGE(tag, "File sending failed!");

                // Abort sending file
                httpd_resp_sendstr_chunk(req, nullptr);

                // Respond with 500 Internal Server Error
                send_error(req, 500, "Failed to read existing file");

                return ESP_FAIL;
            }
        }
    } while (read_bytes > 0);

    // Close file after sending complete
    close(fd);
    ESP_LOGI(tag, "File sending complete");

    // Respond with an empty chunk to signal HTTP response completion
    httpd_resp_send_chunk(req, nullptr, 0);

    return ESP_OK;
}

esp_err_t dispatch_event_handler(httpd_req_t* request)
{
    // Get the socketfd from the session ctx
}

esp_err_t event_get_handler(httpd_req_t* request)
{
    ESP_LOGI(tag, "uri: /api/v1/events");

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

void register_endpoints(httpd_handle_t& server, activity::Context& context)
{
    httpd_uri_t event_uri = {
        .uri = "/api/v1/events",
        .method = HTTP_GET,
        .handler = event_get_handler,
        .user_ctx = nullptr
    };

    httpd_uri_t common_get_uri = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = common_get_handler,
        .user_ctx = &context
    };

    httpd_register_uri_handler(server, &event_uri);
    httpd_register_uri_handler(server, &common_get_uri);
}

esp_err_t on_open(httpd_handle_t server, int sockfd)
{
    ESP_LOGI(tag, "Server socket opened: %d", sockfd);

    // Save socket fd in session context
    httpd_sess_set_ctx(
        server, sockfd, session_sockets_.emplace(sockfd), [](void*) {}
    );

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
