#pragma once

namespace lumen {

/** The main task that handles the firmware.
 *
 * Creates and manages the HTTP server, among other things.
 *
 * \param parameters Unused, but required for FreeRTOS tasks.
 */
void app_task(void* parameters);

} // namespace lumen
