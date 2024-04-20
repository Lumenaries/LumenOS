#include "lumen/hardware/led_pin.hpp"

namespace lumen::hardware {

LEDPin::LEDPin(int pin) : pin_{static_cast<gpio_num_t>(pin)}
{
    gpio_config_t config = {
        .pin_bit_mask = 1ULL << pin,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&config);

    off();
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
