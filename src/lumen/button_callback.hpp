#pragma once

namespace lumen {

/** The handler for a short click of the power button.
 *
 * \param button The handle to the button.
 *
 * \param context The arguments to the callback.
 */
void power_button_single_click(void* button, void* context);

/** The handler for a long press of the power button.
 *
 * \param button The handle to the button.
 *
 * \param context The arguments to the callback.
 */
void power_button_long_press(void* button, void* context);

} // namespace lumen
