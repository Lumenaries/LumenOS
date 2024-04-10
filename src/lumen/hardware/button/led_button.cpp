#include "lumen/hardware/button/led_button.hpp"

#include "lumen/hardware/led_pin.hpp"

namespace lumen::hardware::button {

LEDButton::LEDButton(int32_t button_pin, uint8_t active_level, int led_pin)
    : Button{button_pin, active_level},
      led_pin_{static_cast<gpio_num_t>(led_pin)}
{
    led_pin_init(led_pin_);
}

void LEDButton::set_led(int level)
{
    led_pin_set_level(led_pin_, level);
}

} // namespace lumen::hardware::button
