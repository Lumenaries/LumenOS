#include "lumen/hardware/led_pin.hpp"

namespace lumen::hardware {

LEDPin::LEDPin(int pin) : pin_{static_cast<gpio_num_t>(pin)}
{
    gpio_reset_pin(pin_);
    gpio_set_direction(pin_, GPIO_MODE_OUTPUT);
    gpio_set_level(pin_, 0);
}

void LEDPin::on()
{
    gpio_set_level(pin_, 1);
}

void LEDPin::off()
{
    gpio_set_level(pin_, 0);
}

} // namespace lumen::hardware
