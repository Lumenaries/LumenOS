#pragma once

#include "esp_http_server.h"

#include <string>

namespace lumen::web {

/** Send an error to the client.
 *
 * \param request Request being responded to.
 *
 * \param status Status string, such as 200 for "200 OK".
 *
 * \param message Error message to respond with.
 */
esp_err_t
send_error(httpd_req_t* request, uint status_code, std::string const& message);

} // namespace lumen::web
