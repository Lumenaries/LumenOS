#include "lumen/button_callback.hpp"

#include "lumen/activity/connect.hpp"
#include "lumen/activity/context.hpp"
#include "lumen/hardware/button/button.hpp"
#include "lumen/net/wifi.hpp"

#include "esp_log.h"
#include "esp_sleep.h"

namespace lumen {
namespace {

constexpr auto tag = "button_callback";

} // namespace

void power_button_single_click(void* /* button */, void* context)
{
    // TODO: Before entering deep sleep, save the state of the configured
    // activity
    ESP_LOGI(tag, "Shutting down...");

    auto* button_context = static_cast<hardware::button::ButtonContext*>(context);
    auto* button = button_context->button;

    ESP_ERROR_CHECK(esp_sleep_enable_ext0_wakeup(button->get_pin(), button->get_active_level()));
    esp_deep_sleep_start();
}

void power_button_long_press(void* /* button */, void* context)
{
    ESP_LOGI(tag, "Disconnect the user and reset the password");

    auto* button_context =
        static_cast<hardware::button::ButtonContext*>(context);

    auto* activity_context =
        static_cast<activity::Context*>(button_context->user_context);
    activity_context->set_activity(activity::Type::connect);

    auto* connect_activity =
        static_cast<activity::Connect*>(activity_context->get_activity());

    net::disconnect_user();
    connect_activity->set_connected(false);
}

} // namespace lumen
