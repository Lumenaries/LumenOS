#pragma once

#include "esp_http_server.h"

namespace lumen::web::handler {

/** The default GET handler.
 *
 * \param request Valid pointer to the request being handled.
 */
esp_err_t common_get(httpd_req_t* request);

} // namespace lumen::web::handler
