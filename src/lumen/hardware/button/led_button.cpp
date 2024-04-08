#include "lumen/hardware/button/led_button.hpp"

#include "lumen/hardware/button.hpp"

namespace lumen::hardware::button {

LEDButton::LEDButton(int32_t button_pin, uint8_t active_level)
    : Button(button_pin, active_level)
{
}

int LEDButton::get_led_channel_count() const
{
    return led_channel_count_;
}

bool LEDButton::is_led_supported() const
{
    return led_supported_;
}

bool LEDButton::is_led_active() const
{
    return led_active_;
}

void LEDButton::set_led_supported(bool led_supported)
{
    led_supported_ = led_supported;
}

void LEDButton::set_led_active(bool led_active)
{
    led_active_ = led_active;
}

int LEDButton::get_next_led_channel()
{
    return led_channel_count_++;
}

} // namespace lumen::hardware
