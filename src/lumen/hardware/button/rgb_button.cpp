#include "lumen/hardware/button/rgb_button.hpp"

#include "lumen/hardware/led_pin.hpp"

#include "esp_log.h"

namespace lumen::hardware::button {

RGBButton::RGBButton(
    int32_t button_pin,
    uint8_t active_level,
    int red_pin,
    int green_pin,
    int blue_pin
)
    : Button{button_pin, active_level},
      red_pin_{static_cast<gpio_num_t>(red_pin)},
      green_pin_{static_cast<gpio_num_t>(green_pin)},
      blue_pin_{static_cast<gpio_num_t>(blue_pin)}
{
    // Initialize all LED pins
    led_pin_init(red_pin_);
    led_pin_init(green_pin_);
    led_pin_init(blue_pin_);
}

void RGBButton::set_color(LEDColor color)
{
    switch (color) {
    case LEDColor::none:
        led_pin_set_level(red_pin_, 0);
        led_pin_set_level(green_pin_, 0);
        led_pin_set_level(blue_pin_, 0);
        break;

    case LEDColor::red:
        led_pin_set_level(red_pin_, 1);
        led_pin_set_level(green_pin_, 0);
        led_pin_set_level(blue_pin_, 0);
        break;

    case LEDColor::yellow:
        led_pin_set_level(red_pin_, 1);
        led_pin_set_level(green_pin_, 1);
        led_pin_set_level(blue_pin_, 0);
        break;

    case LEDColor::green:
        led_pin_set_level(red_pin_, 0);
        led_pin_set_level(green_pin_, 1);
        led_pin_set_level(blue_pin_, 0);
        break;

    case LEDColor::cyan:
        led_pin_set_level(red_pin_, 0);
        led_pin_set_level(green_pin_, 1);
        led_pin_set_level(blue_pin_, 1);
        break;

    case LEDColor::blue:
        led_pin_set_level(red_pin_, 0);
        led_pin_set_level(green_pin_, 0);
        led_pin_set_level(blue_pin_, 1);
        break;

    case LEDColor::purple:
        led_pin_set_level(red_pin_, 1);
        led_pin_set_level(green_pin_, 0);
        led_pin_set_level(blue_pin_, 1);
        break;

    case LEDColor::white:
        led_pin_set_level(red_pin_, 1);
        led_pin_set_level(green_pin_, 1);
        led_pin_set_level(blue_pin_, 1);
        break;

    default:
        break;
    }
}

} // namespace lumen::hardware::button
