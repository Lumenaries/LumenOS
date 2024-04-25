#pragma once

#include "esp_http_server.h"

namespace lumen::web::handler {

/** The server-sent event registration endpoint.
 *
 * Clients must set the "Accept" request header to "text/event-stream" in order
 * to subscribe to events published by this endpoint.
 *
 * \param request Valid pointer to the request being handled.
 */
esp_err_t event_get(httpd_req_t* request);

} // namespace lumen::web::handler
