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

/** The handler for a short click of the timer button.
 *
 * \param button The handle to the button.
 *
 * \param context The arguments to the callback.
 */
void timer_button_single_click(void* button, void* context);

/** The handler for a short click of the rocker switch one up switch.
 *
 * \param button The handle to the button.
 *
 * \param context The arguments to the callback.
 */
void rocker_one_up_single_click(void* button, void* context);

/** The handler for a short click of the rocker switch one down switch.
 *
 * \param button The handle to the button.
 *
 * \param context The arguments to the callback.
 */
void rocker_one_down_single_click(void* button, void* context);

/** The handler for a short click of the rocker switch two up switch.
 *
 * \param button The handle to the button.
 *
 * \param context The arguments to the callback.
 */
void rocker_two_up_single_click(void* button, void* context);

/** The handler for a short click of the rocker switch two down switch.
 *
 * \param button The handle to the button.
 *
 * \param context The arguments to the callback.
 */
void rocker_two_down_single_click(void* button, void* context);

} // namespace lumen
