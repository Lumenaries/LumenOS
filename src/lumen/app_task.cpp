#include "lumen/app_task.hpp"

#include "lumen/activity/context.hpp"
#include "lumen/button_callback.hpp"
#include "lumen/hardware/button/led_button.hpp"
#include "lumen/hardware/button/rg_led_button.hpp"
#include "lumen/hardware/button/rocker_switch.hpp"
#include "lumen/net/wifi.hpp"
#include "lumen/web/server.hpp"

namespace lumen {
namespace {

constexpr auto tag = "app_task";

TaskHandle_t app_task_handle = nullptr;

} // namespace

void app_task(void* /* parameters */)
{
    app_task_handle = xTaskGetCurrentTaskHandle();

    auto activity_context = activity::Context{activity::Type::connect};

    net::init_wifi(activity_context);

    auto web_server = web::Server{activity_context};

    auto power_button = hardware::button::RGLEDButton{
        CONFIG_HARDWARE_POWER_BUTTON_PIN,
        CONFIG_HARDWARE_POWER_BUTTON_ACTIVE_LEVEL,
        CONFIG_HARDWARE_POWER_BUTTON_RED_PIN,
        CONFIG_HARDWARE_POWER_BUTTON_GREEN_PIN
    };
    power_button.register_callback(
        BUTTON_SINGLE_CLICK, power_button_single_click, &activity_context
    );
    power_button.register_callback(
        BUTTON_LONG_PRESS_START, power_button_long_press, &activity_context
    );

    power_button.set_color(hardware::button::RGLEDButton::LEDColor::green);

    auto timer_button = hardware::button::LEDButton{
        CONFIG_HARDWARE_TIMER_BUTTON_PIN,
        CONFIG_HARDWARE_TIMER_BUTTON_ACTIVE_LEVEL,
        CONFIG_HARDWARE_TIMER_BUTTON_WHITE_PIN
    };
    timer_button.register_callback(
        BUTTON_PRESS_DOWN, timer_button_press_down, &activity_context
    );
    timer_button.register_callback(
        BUTTON_PRESS_UP, timer_button_press_up, nullptr
    );

    auto rocker_one = hardware::button::RockerSwitch{
        CONFIG_HARDWARE_ROCKER_SWITCH_ONE_UP,
        CONFIG_HARDWARE_ROCKER_SWITCH_ONE_UP_ACTIVE_LEVEL,
        CONFIG_HARDWARE_ROCKER_SWITCH_ONE_DOWN,
        CONFIG_HARDWARE_ROCKER_SWITCH_ONE_DOWN_ACTIVE_LEVEL
    };
    rocker_one.up().register_callback(
        BUTTON_SINGLE_CLICK, rocker_one_up_single_click, &activity_context
    );
    rocker_one.down().register_callback(
        BUTTON_SINGLE_CLICK, rocker_one_down_single_click, &activity_context
    );

    auto rocker_two = hardware::button::RockerSwitch{
        CONFIG_HARDWARE_ROCKER_SWITCH_TWO_UP,
        CONFIG_HARDWARE_ROCKER_SWITCH_TWO_UP_ACTIVE_LEVEL,
        CONFIG_HARDWARE_ROCKER_SWITCH_TWO_DOWN,
        CONFIG_HARDWARE_ROCKER_SWITCH_TWO_DOWN_ACTIVE_LEVEL
    };
    rocker_two.up().register_callback(
        BUTTON_SINGLE_CLICK, rocker_two_up_single_click, &activity_context
    );
    rocker_two.down().register_callback(
        BUTTON_SINGLE_CLICK, rocker_two_down_single_click, &activity_context
    );

    uint32_t event_buffer{};

    while (true) {
        xTaskNotifyWait(pdFALSE, ULONG_MAX, &event_buffer, portMAX_DELAY);

        if ((event_buffer & g_update_display_signal) != 0) {
            activity_context.update_display();

            web::send_event_message(
                web::EventMessage{web::EventMessage::Type::event_occurred}
            );
        }
    }
}

TaskHandle_t get_app_task_handle()
{
    return app_task_handle;
}

} // namespace lumen
