#pragma once

#include "esp_http_server.h"

namespace lumen::web::handler {

esp_err_t football_put(httpd_req_t* request);

} // namespace lumen::web::handler
