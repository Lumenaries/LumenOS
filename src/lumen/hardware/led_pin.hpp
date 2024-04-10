#pragma once

#include "driver/gpio.h"

namespace lumen::hardware {

/** Initialize an LED GPIO pin.
 *
 * \param led_pin The GPIO number of the LED.
 */
void led_pin_init(gpio_num_t led_pin);

/** Set the GPIO level of an LED pin.
 *
 * \param led_pin The GPIO number of the LED.
 *
 * \param level The level of the GPIO pin.
 * A value of zero will turn off the LED.
 * A non-zero positive integer will turn on the LED.
 */
void led_pin_set_level(gpio_num_t led_pin, uint32_t level);

} // namespace lumen::hardware
