#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace lumen {

constexpr auto g_update_display_signal = 0x01UL;

/** The main task that handles the firmware.
 *
 * Creates and manages the HTTP server, among other things.
 *
 * \param parameters Unused, but required for FreeRTOS tasks.
 */
void app_task(void* parameters);

TaskHandle_t get_app_task_handle();

} // namespace lumen
