#pragma once

#include "driver/gpio.h"

namespace lumen::hardware {

/// Define a GPIO pin with an LED.
class LEDPin {
public:
    /** LEDPin constructor.
     *
     * \param pin The GPIO number of the LED.
     */
    LEDPin(int pin);

    /// Turn on the LED pin.
    void on();

    /// Turn off the LED pin.
    void off();

private:
    gpio_num_t pin_;
};

} // namespace lumen::hardware
