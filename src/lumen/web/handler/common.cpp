#include "lumen/web/handler/common.hpp"

#include "esp_log.h"
#include "esp_vfs.h"

#include <fcntl.h>

namespace lumen::web::handler {
namespace {

constexpr auto tag = "web/handler/common";

/* Compare the extension of the filepath with a given extension.
 *
 * \param filepath The path to the file.
 * \param ext The extension to compare the file to.
 *
 * \returns true if the filepath extension matches the given extension.
 * \returns false if the filepath extension does not match the given extension.
 */
bool check_file_extension(char const* filepath, char const* ext);

/** Set the type of the response based on the file extension.
 *
 * \param req Pointer to the request being handled.
 * \param filepath The path to the file to be opened.
 */
esp_err_t set_content_type_from_file(httpd_req_t* req, char const* filepath);

} // namespace

esp_err_t common_get(httpd_req_t* req)
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

        // Respond with 500 Internal Server Error
        httpd_resp_send_err(
            req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to read existing file"
        );
        return ESP_FAIL;
    }

    set_content_type_from_file(req, filepath);

    // TODO: Allocate this 10240 bytes outside of the http task to reduce load
    // times
    uint32_t scratch_buffer_size = 1024;
    char chunk[scratch_buffer_size];
    ssize_t read_bytes;

    do {
        // Read the file in the scratch buffer in chunks
        read_bytes = read(fd, chunk, scratch_buffer_size);

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
                httpd_resp_send_err(
                    req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to send file"
                );

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

namespace {

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

} // namespace

} // namespace lumen::web::handler
