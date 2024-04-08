#pragma once

#include "lumen/hardware/button/led_button.hpp"
#include "lumen/hardware/led_pin.hpp"

namespace lumen::hardware::button {

/// A button with a 3-pin RGB LED.
class RGBButton : public LEDButton {
public:
    /// Supported colors for an RGB LED button.
    enum class LEDColor {
        red = 0,
        orange,
        yellow,
        green,
        blue,
        purple,
        white,
        none,
    };

    /** RGBButton constructor.
     *
     * \param button_pin The GPIO pin number of the button.
     *
     * \param active_level The GPIO level (high or low) when the button is
     * pressed. If the active level is high, input a non-zero positive. If low,
     * input 0.
     *
     * \param red_pin The GPIO pin number of the red LED.
     *
     * \param green_pin The GPIO pin number of the green LED.
     *
     * \param blue_pin The GPIO pin number of the blue LED.
     */
    RGBButton(
        int32_t button_pin,
        uint8_t active_level,
        int red_pin,
        int green_pin,
        int blue_pin
    );

    /** Set the color of the RGB LED.
     *
     * \param color The supported LED color.
     */
    esp_err_t set_color(LEDColor color);

private:
    LEDPin red_led_{};
    LEDPin green_led_{};
    LEDPin blue_led_{};
};

} // namespace lumen::hardware
