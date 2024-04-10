#include "lumen/hardware/led_pin.hpp"

namespace lumen::hardware {

void led_pin_init(gpio_num_t led_pin)
{
    gpio_reset_pin(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
    gpio_set_level(led_pin, 0);
}

void led_pin_set_level(gpio_num_t led_pin, uint32_t level)
{
    gpio_set_level(led_pin, level);
}

}
