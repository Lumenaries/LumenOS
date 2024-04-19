#include "lumen/button_callback.hpp"

#include "lumen/activity/connect.hpp"
#include "lumen/activity/context.hpp"
#include "lumen/net/wifi.hpp"

#include "esp_log.h"

namespace lumen {
namespace {

constexpr auto tag = "button_callback";

} // namespace

void timer_button_long_press(void* /* button */, void* context)
{
    // TODO: Check the state of the system.
    // If we are in low power mode, we should flash the battery status.
    // If we are not in low power mode, we should disconnect the user.
    ESP_LOGI(tag, "Registered a long click from the power button");

    auto* activity_context = static_cast<activity::Context*>(context);
    activity_context->set_activity(activity::Type::connect);

    auto* connect_activity =
        static_cast<activity::Connect*>(activity_context->get_activity());

    net::disconnect_user();
    connect_activity->set_connected(false);
}

} // namespace lumen
