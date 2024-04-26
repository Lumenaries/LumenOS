#include "lumen/web/handler/soccer.hpp"

#include "lumen/activity/activity.hpp"
#include "lumen/activity/soccer.hpp"
#include "lumen/web/error.hpp"
#include "lumen/web/server.hpp"

#include "esp_log.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace lumen::web::handler {
namespace {

constexpr auto tag = "web/handler/soccer";

constexpr auto buffer_size = 128;

}

esp_err_t soccer_get(httpd_req_t* request)
{
    auto* activity_context =
        static_cast<Server*>(httpd_get_global_user_ctx(request->handle))
            ->get_activity_context();

    activity_context->set_activity(activity::Type::soccer);

    auto soccer_data = activity_context->get_activity_json();

    httpd_resp_set_type(request, "application/json");
    httpd_resp_sendstr(request, soccer_data.dump().c_str());

    return ESP_OK;
}

esp_err_t soccer_put(httpd_req_t* request)
{
    ESP_LOGI(tag, "Soccer PUT handler");
    // Make sure the correct endpoint was hit
    auto* activity_context =
        static_cast<Server*>(httpd_get_global_user_ctx(request->handle))
            ->get_activity_context();

    if (activity_context->get_activity_type() != activity::Type::soccer) {
        ESP_LOGW(
            tag,
            "Current activity is not soccer: %d",
            static_cast<int>(activity_context->get_activity_type())
        );

        return send_error(request, 400, "The current activity is not soccer");
    }

    // Make sure we can store the request JSON in our buffer
    auto const content_length = request->content_len;

    if (content_length > buffer_size - 1) {
        ESP_LOGW(tag, "Received more data than can be processed");
        return send_error(
            request, 500, "More data was received than can be processed"
        );
    }

    char buffer[buffer_size];

    // Read in the request JSON
    int received_bytes = httpd_req_recv(request, buffer, buffer_size);
    buffer[content_length] = '\0';

    if (received_bytes <= 0) {
        return send_error(request, 500, "Error reading request content");
    }

    auto const request_json = json::parse(buffer);

    ESP_LOGI(tag, "Request: %s", request_json.dump().c_str());

    auto* soccer =
        static_cast<activity::Soccer*>(activity_context->get_activity());

    // Parse and validate the request JSON

    if (request_json.contains("teamOne")) {
        if (request_json["teamOne"].contains("name")) {
            auto name = request_json["teamOne"]["name"];

            // Set a limit of six characters
            if (name.is_string() && name.size() <= 6) {
                soccer->team_one().name().set_value(name);
            }
        }
        if (request_json["teamOne"].contains("score")) {
            auto score = request_json["teamOne"]["score"];

            if (score.is_number_unsigned()) {
                soccer->team_one().score().set_value(score);
            }
        }
    }

    if (request_json.contains("teamTwo")) {
        if (request_json["teamTwo"].contains("name")) {
            auto name = request_json["teamTwo"]["name"];

            // Set a limit of six characters
            if (name.is_string() && name.size() <= 6) {
                soccer->team_two().name().set_value(name);
            }
        }
        if (request_json["teamTwo"].contains("score")) {
            auto score = request_json["teamTwo"]["score"];

            if (score.is_number_unsigned()) {
                soccer->team_two().score().set_value(score);
            }
        }
    }

    if (request_json.contains("half") &&
        request_json["half"].is_number_unsigned()) {
        soccer->half().set_value(request_json["half"]);
    }

    if (request_json.contains("timer")) {
        if (request_json["timer"].contains("isRunning") &&
            request_json["timer"]["isRunning"].is_boolean()) {
            if (request_json["timer"]["isRunning"]) {
                if (soccer->timer().get_value() > 0) {
                    soccer->timer().start();
                } else {
                    soccer->timer().reset();
                    soccer->timer().start();
                }
            } else {
                soccer->timer().stop();
            }
        }

        if (request_json["timer"].contains("value") &&
            request_json["timer"]["value"].is_number_unsigned()) {
            soccer->timer().set_value(request_json["timer"]["value"]);
        }
    }

    httpd_resp_send(request, nullptr, 0);
    return ESP_OK;
}

} // namespace lumen::web::handler
