#pragma once

#include "lumen/hardware/led_button.hpp"
#include "lumen/hardware/led_pin.hpp"

namespace lumen::hardware {

/// A button with a single LED pin.
class SingleLEDButton : public LEDButton {
public:
    /** Construct a button with one LED.
     *
     * \param button_pin The GPIO pin number of the button.
     * \param active_level The GPIO level when the button is pressed.
     * \param led_pin The GPIO pin number of the LED.
     */
    SingleLEDButton(int32_t button_pin, uint8_t active_level, int led_pin);

    /** Set the active level of the button's LED.
     *
     * \param duty_percentage A range from 0 to 100 that is a percentage of the
     * max duty resolution.
     */
    esp_err_t set_led(uint32_t duty_percentage);

private:
    LEDPin led_;
};

} // namespace lumen::hardware
