#include "lumen/web/handler/event.hpp"

#include "lumen/web/error.hpp"
#include "lumen/web/event.hpp"

#include <cstring> // strcmp

namespace lumen::web::handler {

esp_err_t event_get_handler(httpd_req_t* request)
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

    auto* server =
        static_cast<Server*>(httpd_get_global_user_ctx(request->handle));

    // Attempt to set the event stream
    if (server->set_event_stream(request) == ESP_OK) {
        return ESP_OK;
    } else {
        return send_error(
            request, 503, "No event handler threads are available."
        );
    }

    // if (dispatch_event_handler(request) == ESP_OK) {
    //     return ESP_OK;
    // } else {
    //     return send_error(
    //         request, 503, "No event handler threads are available."
    //     );
    // }
}

} // namespace lumen::web::handler
