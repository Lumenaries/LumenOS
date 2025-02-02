#pragma once

#include "lumen/hardware/button/button.hpp"

#include "lumen/hardware/led_pin.hpp"

#include "driver/gpio.h"

namespace lumen::hardware::button {

/// Defines an button with a single LED.
class LEDButton : public Button {
public:
    /* LEDButton constructor.
     *
     * \param button_pin The GPIO number of the button.
     *
     * \param active_level The GPIO level (high or low) when the button is
     * pressed.
     * A value of 0 will set the GPIO level to low.
     * A non-zero positive integer will set the GPIO level to high.
     *
     * \param led_pin The GPIO number of the LED.
     */
    LEDButton(int32_t button_pin, uint8_t active_level, int led_pin);

    /* Set the level of the LED GPIO pin.
     *
     * \param on A value of `true` will turn on the LED.
     * A value of `false` will turn off the LED.
     */
    void set_led(bool on);

private:
    LEDPin led_pin_;
};

} // namespace lumen::hardware::button
