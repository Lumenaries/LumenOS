#pragma once

#include "lumen/hardware/button/button.hpp"

#include "driver/gpio.h"

namespace lumen::hardware::button {

/// Defines a button with 3-pin RGB LEDs.
class RGBButton : public Button {
public:
    /// Supported colors for an RGB LED button.
    enum class LEDColor {
        none = 0,
        red,
        yellow,
        green,
        cyan,
        blue,
        purple,
        white,
    };

    /** RGBButton constructor.
     *
     * \param button_pin The GPIO pin number of the button.
     *
     * \param active_level The GPIO level (high or low) when the button is
     * pressed.
     * A value of 0 will set the GPIO level to low.
     * A non-zero positive integer will set the GPIO level to high.
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
    void set_color(LEDColor color);

private:
    gpio_num_t red_pin_;
    gpio_num_t green_pin_;
    gpio_num_t blue_pin_;
};

} // namespace lumen::hardware::button
