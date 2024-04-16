#include "lumen/app_task.hpp"

#include "lumen/activity/context.hpp"
#include "lumen/button_callback.hpp"
#include "lumen/hardware/button/rg_led_button.hpp"
#include "lumen/net/wifi.hpp"
#include "lumen/web/server.hpp"

#include "esp_log.h"

#include "freertos/task.h"

#include "esp_wifi.h"

namespace lumen {
namespace {

constexpr auto tag = "app_task";

} // namespace

void app_task(void* /* parameters */)
{
    auto activity_context = activity::Context{activity::Type::connect};

    ESP_LOGI(tag, "Activity addr %p", &activity_context);
    switch (activity_context.get_activity_type()) {
    case activity::Type::none:
        ESP_LOGI(tag, "none");
        break;
    case activity::Type::connect:
        ESP_LOGI(tag, "connect");
        break;
    default:
        ESP_LOGI(tag, "no type");
    }

    net::init_wifi(activity_context);

    auto web_server = web::Server{activity_context};

    auto power_button = hardware::button::RGLEDButton{
        CONFIG_HARDWARE_POWER_BUTTON_PIN,
        CONFIG_HARDWARE_POWER_BUTTON_ACTIVE_LEVEL,
        CONFIG_HARDWARE_POWER_BUTTON_RED_PIN,
        CONFIG_HARDWARE_POWER_BUTTON_GREEN_PIN
    };
    power_button.register_callback(
        BUTTON_LONG_PRESS_START, power_button_long_press, &activity_context
    );

    // TODO: register a callback function on the power button for a single
    // press. This will turn on the product.

    while (true) {
        power_button.set_color(hardware::button::RGLEDButton::LEDColor::none);
        vTaskDelay(1000);
        power_button.set_color(hardware::button::RGLEDButton::LEDColor::red);
        vTaskDelay(1000);
        power_button.set_color(hardware::button::RGLEDButton::LEDColor::yellow);
        vTaskDelay(1000);
        power_button.set_color(hardware::button::RGLEDButton::LEDColor::green);
        vTaskDelay(1000);
    }
}

} // namespace lumen
