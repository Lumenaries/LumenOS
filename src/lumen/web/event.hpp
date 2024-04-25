#pragma once

#include "esp_http_server.h"

namespace lumen::web {

struct EventMessage {
    enum class Type {
        none,
        event_stream_closed,
        event_stream_started,
        event_occurred,
    };

    Type type{};
    httpd_req_t* new_request{};

    explicit EventMessage(Type type = Type::none);
    EventMessage(Type type, httpd_req_t* new_request);
};

esp_err_t dispatch_event_handler(httpd_req_t* request);

} // namespace lumen::web
