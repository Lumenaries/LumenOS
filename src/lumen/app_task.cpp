#include "lumen/app_task.hpp"

#include "lumen/activity/context.hpp"
#include "lumen/web/server.hpp"

namespace lumen {
namespace {

constexpr auto tag = "app_task";
TaskHandle_t app_task_handle = nullptr;

} // namespace

void app_task(void* /* parameters */)
{
    app_task_handle = xTaskGetCurrentTaskHandle();

    auto activity_context = activity::Context{};

    auto web_server = web::Server{activity_context};

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
