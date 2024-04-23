#pragma once

#include "esp_http_server.h"

namespace lumen::web::handler {

/** The put handler for the football endpoint.
 *
 * \param request Valid pointer to the request being handled.
 */
esp_err_t football_put(httpd_req_t* request);

} // namespace lumen::web::handler
