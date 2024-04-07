#include "lumen/web/handler/football.hpp"

#include "lumen/activity/context.hpp"
#include "lumen/activity/football.hpp"

#include "esp_log.h"

namespace lumen::web::handler {
namespace {

constexpr auto tag = "web/handler";

} // namespace

esp_err_t football_put(httpd_req_t* request)
{
    auto* context = static_cast<activity::Context*>(request->user_ctx);

    if (context->get_activity_type() != activity::Type::Football) {
        return ESP_FAIL;
    }

    auto* football = static_cast<activity::Football*>(context->get_activity());

    football->team_one().score().increase();

    // ESP_LOGI(
    //     tag,
    //     "Football PUT handler: %d",
    //     football->team_one().score().increase().get_value()
    //);

    httpd_resp_send(request, nullptr, 0);

    return ESP_OK;
}

} // namespace lumen::web::handler
