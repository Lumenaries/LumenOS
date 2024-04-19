#include "lumen/app_task.hpp"

#include "lumen/activity/context.hpp"
#include "lumen/button_callback.hpp"
#include "lumen/hardware/button/led_button.hpp"
#include "lumen/hardware/button/rg_led_button.hpp"
#include "lumen/net/wifi.hpp"
#include "lumen/web/server.hpp"

#include "esp_log.h"
#include "freertos/task.h"

namespace lumen {
namespace {

constexpr auto tag = "app_task";

} // namespace

void app_task(void* /* parameters */)
{
    auto activity_context = activity::Context{activity::Type::connect};

    net::init_wifi(activity_context);

    auto web_server = web::Server{activity_context};

    auto power_button = hardware::button::RGLEDButton{
        CONFIG_HARDWARE_POWER_BUTTON_PIN,
        CONFIG_HARDWARE_POWER_BUTTON_ACTIVE_LEVEL,
        CONFIG_HARDWARE_POWER_BUTTON_RED_PIN,
        CONFIG_HARDWARE_POWER_BUTTON_GREEN_PIN
    };

    // TODO: register a callback function on the power button for a single
    // press. This will turn on the product.

    auto timer_button = hardware::button::LEDButton{
        CONFIG_HARDWARE_TIMER_BUTTON_PIN,
        CONFIG_HARDWARE_TIMER_BUTTON_ACTIVE_LEVEL,
        CONFIG_HARDWARE_TIMER_BUTTON_WHITE_PIN
    };
    timer_button.register_callback(
        BUTTON_LONG_PRESS_START, timer_button_long_press, &activity_context
    );

    while (true) {
        vTaskDelay(1000);
    }
}

} // namespace lumen
