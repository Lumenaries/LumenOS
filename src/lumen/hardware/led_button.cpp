#include "lumen/hardware/led_button.hpp"

#include "lumen/hardware/button.hpp"

namespace lumen::hardware {

LEDButton::LEDButton(int32_t button_pin, uint8_t active_level)
    : Button(button_pin, active_level)
{
}

int LEDButton::get_channel_count()
{
    return channel_count_;
}

bool LEDButton::is_led_supported()
{
    return led_supported_;
}

bool LEDButton::is_led_active()
{
    return led_active_;
}

void LEDButton::set_channel_count(int channel_count)
{
    channel_count_ = channel_count;
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
    return channel_count_++;
}

} // namespace lumen::hardware
