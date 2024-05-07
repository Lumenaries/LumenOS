#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace lumen {

constexpr auto g_update_display_signal = 0x01UL;
constexpr auto g_update_event_stream = 0x02UL;
constexpr auto g_swap_to_default_activity = 0x04UL;

TaskHandle_t get_app_task_handle();

/** The main task that handles the firmware.
 *
 * Creates and manages the HTTP server, among other things.
 *
 * \param parameters Unused, but required for FreeRTOS tasks.
 */
void app_task(void* parameters);

/** Send a signal to the app task.
 *
 * By default, this function will signal an update to the display and the
 * client event stream.
 */
void signal_update(
    uint32_t signal = g_update_display_signal | g_update_event_stream
);

/** Send a signal to the app task.
 *
 * By default, this function will signal an update to the display and the
 * client event stream.
 */
bool signal_update_from_isr(
    uint32_t signal = g_update_display_signal | g_update_event_stream
);

} // namespace lumen
