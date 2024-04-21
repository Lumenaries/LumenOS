#include "lumen/app_task.hpp"

#include "lumen/activity/context.hpp"
#include "lumen/button_callback.hpp"
#include "lumen/hardware/button/rg_led_button.hpp"
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
        BUTTON_SINGLE_CLICK, power_button_single_click, nullptr
    );
    power_button.register_callback(
        BUTTON_LONG_PRESS_START, power_button_long_press, &activity_context
    );

    uint32_t event_buffer{};

    while (true) {
        xTaskNotifyWait(pdFALSE, ULONG_MAX, &event_buffer, portMAX_DELAY);

        if ((event_buffer & g_update_display_signal) != 0) {
            activity_context.update_display();
        }
    }
}

TaskHandle_t get_app_task_handle()
{
    return app_task_handle;
}

} // namespace lumen
