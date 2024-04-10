#include "lumen/hardware/button/led_button.hpp"

#include "lumen/hardware/led_pin.hpp"

namespace lumen::hardware::button {

LEDButton::LEDButton(int32_t button_pin, uint8_t active_level, int led_pin)
    : Button{button_pin, active_level}, led_pin_{led_pin}
{
}

void LEDButton::set_led(bool on)
{
    if (on) {
        led_pin_.on();
        return;
    }

    led_pin_.off();
}

} // namespace lumen::hardware::button
