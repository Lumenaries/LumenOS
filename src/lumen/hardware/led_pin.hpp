#pragma once

#include "driver/ledc.h"

namespace lumen::hardware {

/// Defines an LED on a GPIO pin.
class LEDPin {
public:
    LEDPin() = default;

    /** LEDPin constructor.
     *
     * \param pin The GPIO pin number.
     *
     * \param channel The LED channel.
     */
    LEDPin(int pin, int channel_num);

    [[nodiscard]] uint32_t get_duty() const;

    /** Setter for the channel duty.
     *
     * \param duty_percentage A range from 0 to 100 that is a percentage of the
     * max duty resolution.
     *
     * \returns ESP_OK on success.
     *
     * \returns ESP_ERR_INVALID_ARG if `duty_percentage` is greater than 100.
     */
    esp_err_t set_duty(uint32_t duty_percentage);

private:
    ledc_timer_config_t timer_config_;
    ledc_channel_config_t channel_config_;

    uint8_t duty_resolution_{};
    uint8_t max_duty_{};
};

} // namespace lumen::hardware
