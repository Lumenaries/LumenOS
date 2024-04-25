#include "lumen/web/handler/advertisement.hpp"

#include "lumen/activity/context.hpp"
#include "lumen/web/error.hpp"
#include "lumen/web/server.hpp"

#include "esp_log.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace lumen::web::handler {
namespace {

constexpr auto tag = "web/handler/advertisement";

constexpr auto buffer_size = 128;

} // namespace

esp_err_t advertisement_get(httpd_req_t* request)
{
    auto* activity_context =
        static_cast<Server*>(httpd_get_global_user_ctx(request->handle))
            ->get_activity_context();

    auto advertisements = activity_context->get_advertisement_json();

    httpd_resp_set_type(request, "application/json");
    httpd_resp_sendstr(request, advertisements.dump().c_str());

    return ESP_OK;
}

esp_err_t advertisement_post(httpd_req_t* request)
{
    // Make sure we can store the request JSON in our buffer
    auto const content_length = request->content_len;

    if (content_length > buffer_size - 1) {
        return send_error(
            request, 500, "More data was received than can be processed"
        );
    }

    char buffer[buffer_size];

    // Read in the request JSON
    int received_bytes = httpd_req_recv(request, buffer, buffer_size);
    buffer[content_length] = '\0';

    if (received_bytes <= 0) {
        return send_error(request, 500, "Error reading request context");
    }

    auto const request_json = json::parse(buffer);

    if (request_json.contains("ad")) {
        auto ad = request_json["ad"];

        if (ad.is_string() && 0 < ad.size() && ad.size() <= 50) {
            auto* activity_context =
                static_cast<Server*>(httpd_get_global_user_ctx(request->handle))
                    ->get_activity_context();

            json ad_id = {{"id", activity_context->add_advertisement(ad)}};

            httpd_resp_set_type(request, "application/json");
            httpd_resp_sendstr(request, ad_id.dump().c_str());
        }
    }

    return ESP_OK;
}

esp_err_t advertisement_delete(httpd_req_t* request)
{
    // Make sure we can store the request JSON in our buffer
    auto const content_length = request->content_len;

    if (content_length > buffer_size - 1) {
        return send_error(request, 500, "Error reading request context");
    }

    char buffer[buffer_size];

    // Read in the request JSON
    int received_bytes = httpd_req_recv(request, buffer, buffer_size);
    buffer[content_length] = '\0';

    if (received_bytes <= 0) {
        return send_error(request, 500, "Error reading request content");
    }

    auto const request_json = json::parse(buffer);

    if (request_json.contains("adId")) {
        auto ad_id = request_json["adId"];

        if (ad_id.is_number_unsigned()) {
            auto* activity_context =
                static_cast<Server*>(httpd_get_global_user_ctx(request->handle))
                    ->get_activity_context();

            activity_context->delete_advertisement(ad_id.get<int>());
            json data = activity_context->get_advertisement_json();

            httpd_resp_set_type(request, "application/json");
            httpd_resp_sendstr(request, data.dump().c_str());
        }
    }

    return ESP_OK;
}

} // namespace lumen::web::handler
