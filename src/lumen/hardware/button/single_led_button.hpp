#pragma once

#include "lumen/hardware/button/led_button.hpp"
#include "lumen/hardware/led_pin.hpp"

namespace lumen::hardware::button {

/// A button with a single LED pin.
class SingleLEDButton : public LEDButton {
public:
    /** Construct a button with one LED.
     *
     * \param button_pin The GPIO pin number of the button.
     *
     * \param active_level The GPIO level (high or low) when the button is
     * pressed. If the active level is high, input a non-zero positive. If low,
     * input 0.
     *
     * \param led_pin The GPIO pin number of the LED.
     */
    SingleLEDButton(int32_t button_pin, uint8_t active_level, int led_pin);

    /** Set the brightness of the button's LED.
     *
     * \param duty_percentage A range from 0 to 100 that is a percentage of the
     * max duty resolution.
     *
     * \returns ESP_OK on success.
     *
     * \returns ESP_ERR_INVALID_ARG if `duty_percentage` is greater than 100.
     */
    esp_err_t set_led_brightness(uint32_t duty_percentage);

private:
    LEDPin led_{};
};

} // namespace lumen::hardware
