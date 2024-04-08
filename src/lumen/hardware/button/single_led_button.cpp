#include "lumen/hardware/button/single_led_button.hpp"

#include "lumen/hardware/led_pin.hpp"

#include "driver/ledc.h"
#include "esp_log.h"

namespace lumen::hardware::button {

SingleLEDButton::SingleLEDButton(
    int32_t button_pin,
    uint8_t active_level,
    int led_pin
)
    : LEDButton{button_pin, active_level}
{
    // Check if there is an available LED channel.
    if (get_led_channel_count() < static_cast<int>(LEDC_CHANNEL_MAX)) {
        led_ = LEDPin{led_pin, get_next_led_channel()};
        set_led_supported(true);
    } else {
        ESP_LOGE("lumen/hardware/button", "Unable to initialize LED pins.");
        set_led_supported(false);
    }
}

esp_err_t SingleLEDButton::set_led_brightness(uint32_t duty_percentage)
{
    if (!is_led_supported()) {
        return ESP_ERR_NOT_SUPPORTED;
    }

    auto ret = led_.set_duty(duty_percentage);
    if (ret == ESP_OK) {
        // Set the LED to be active if the duty is greater than 0.
        set_led_active(duty_percentage > 0);
    }

    return ret;
}

} // namespace lumen::hardware::button
