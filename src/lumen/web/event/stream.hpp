#pragma once

#include "esp_http_server.h"

namespace lumen::web::event {

class Stream {
public:
    explicit Stream(httpd_req_t* request);

private:
};

} // namespace lumen::web::event
