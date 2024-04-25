#pragma once

#include "esp_http_server.h"

namespace lumen::web::handler {

/** The GET handler for the advertisement endpoint.
 *
 * \param request Valid pointer to the request being handled.
 */
esp_err_t advertisement_get(httpd_req_t* request);

/** The POST handler for the advertisement endpoint.
 *
 * \param request Valid pointer to the request being handled.
 */
esp_err_t advertisement_post(httpd_req_t* request);

/** The DELETE handler for the advertisement endpoint.
 *
 * \param request Valid pointer to the request being handled.
 */
esp_err_t advertisement_delete(httpd_req_t* request);

} // namespace lumen::web::handler
