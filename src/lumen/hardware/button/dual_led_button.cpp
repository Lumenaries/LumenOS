#include "lumen/hardware/button/dual_led_button.hpp"

#include "esp_log.h"

namespace lumen::hardware::button {

DualLEDButton::DualLEDButton(
    int32_t button_pin,
    uint8_t active_level,
    int red_pin,
    int green_pin
)
    : Button{button_pin, active_level}, red_pin_{red_pin}, green_pin_{green_pin}
{
}

void DualLEDButton::set_color(LEDColor color)
{
    switch (color) {
    case LEDColor::none:
        red_pin_.off();
        green_pin_.off();
        break;

    case LEDColor::red:
        red_pin_.on();
        green_pin_.off();
        break;

    case LEDColor::yellow:
        red_pin_.on();
        green_pin_.on();
        break;

    case LEDColor::green:
        red_pin_.off();
        green_pin_.on();
        break;

    default:
        break;
    }
}

} // namespace lumen::hardware::button
