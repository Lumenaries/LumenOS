#include "lumen/web/handler/event.hpp"

#include "lumen/web/error.hpp"
#include "lumen/web/server.hpp"

#include <cstring> // strcmp

namespace lumen::web::handler {

esp_err_t event_get(httpd_req_t* request)
{
    auto header_len = httpd_req_get_hdr_value_len(request, "Accept");
    char buffer[header_len + 1] = {0};

    httpd_req_get_hdr_value_str(request, "Accept", buffer, header_len + 1);

    if (strcmp(buffer, "text/event-stream") != 0) {
        return send_error(
            request, 400, "Accept header is not 'text/event-stream'."
        );
    }

    httpd_resp_set_type(request, "text/event-stream");

    // Check if the event stream task is available
    if (dispatch_event_handler(request) == ESP_OK) {
        return ESP_OK;
    } else {
        return send_error(
            request, 503, "No event handler threads are available."
        );
    }
}

} // namespace lumen::web::handler
