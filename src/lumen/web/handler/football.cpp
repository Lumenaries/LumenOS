#include "lumen/web/handler/football.hpp"

#include "lumen/activity/context.hpp"
#include "lumen/activity/football.hpp"

#include "esp_log.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace lumen::web::handler {
namespace {

constexpr auto tag = "web/handler/football";

constexpr auto buffer_size = 128;

} // namespace

esp_err_t football_put(httpd_req_t* request)
{
    // Make sure the correct endpoint was hit
    auto* context = static_cast<activity::Context*>(request->user_ctx);

    if (context->get_activity_type() != activity::Type::football) {
        ESP_LOGW(
            tag,
            "Current activity is not football: %d",
            static_cast<int>(context->get_activity_type())
        );
        httpd_resp_send(request, nullptr, 0);
        return ESP_FAIL;
    }

    // Make sure we can store the request JSON in our buffer
    auto const content_length = request->content_len;

    if (content_length > buffer_size - 1) {
        ESP_LOGW(tag, "Received more data than can be processed");
        httpd_resp_send_500(request);
        return ESP_FAIL;
    }

    char buffer[buffer_size];

    // Read in the request JSON
    int received_bytes = httpd_req_recv(request, buffer, buffer_size);
    buffer[content_length] = '\0';

    if (received_bytes <= 0) {
        ESP_LOGW(tag, "Error reading request content");
        httpd_resp_send_500(request);
        return ESP_FAIL;
    }

    auto const request_json = json::parse(buffer);

    auto* football = static_cast<activity::Football*>(context->get_activity());

    // Parse and validate the request JSON

    if (request_json.contains("teamOne")) {
        if (request_json["teamOne"].contains("name")) {
            auto name = request_json["teamOne"]["name"];

            if (name.is_string()) {
                football->team_one().name().set_value(name);
            }
        }
        if (request_json["teamOne"].contains("score")) {
            auto score = request_json["teamOne"]["score"];

            if (score.is_number_unsigned()) {
                football->team_one().score().set_value(score);
            }
        }
    }

    if (request_json.contains("teamTwo")) {
        if (request_json["teamTwo"].contains("name")) {
            auto name = request_json["teamTwo"]["name"];

            if (name.is_string()) {
                football->team_two().name().set_value(name);
            }
        }
        if (request_json["teamTwo"].contains("score")) {
            auto score = request_json["teamTwo"]["score"];

            if (score.is_number_unsigned()) {
                football->team_two().score().set_value(score);
            }
        }
    }

    if (request_json.contains("down") &&
        request_json["down"].is_number_unsigned()) {
        football->down().set_value(request_json["down"]);
    }

    if (request_json.contains("quarter") &&
        request_json["quarter"].is_number_unsigned()) {
        football->quarter().set_value(request_json["quarter"]);
    }

    if (request_json.contains("yards") &&
        request_json["yards"].is_number_unsigned()) {
        football->yards().set_value(request_json["yards"]);
    }

    if (request_json.contains("timer")) {
        if (request_json["timer"].contains("isRunning") &&
            request_json["timer"]["isRunning"].is_boolean()) {
            if (request_json["timer"]["isRunning"]) {
                if (football->timer().get_value() > 0) {
                    football->timer().start();
                } else {
                    football->timer().reset();
                    football->timer().start();
                }
            } else {
                football->timer().stop();
            }
        }

        if (request_json["timer"].contains("value") &&
            request_json["timer"]["timer"].is_number_unsigned()) {
            football->timer().set_value(request_json["timer"]["value"]);
        }
    }

    httpd_resp_send(request, nullptr, 0);
    return ESP_OK;
}

} // namespace lumen::web::handler
