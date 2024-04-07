#include "lumen/hardware/single_led_button.hpp"

#include "lumen/hardware/led_pin.hpp"

#include "driver/ledc.h"
#include "esp_log.h"

namespace lumen::hardware {
namespace {

constexpr auto tag = "lumen/hardware";

} // namespace

SingleLEDButton::SingleLEDButton(
    int32_t button_pin,
    uint8_t active_level,
    int led_pin
)
    : LEDButton{button_pin, active_level}
{
    // Check if there is an available LED channel.
    if (get_channel_count() < static_cast<int>(LEDC_CHANNEL_MAX)) {
        led_ = LEDPin{led_pin, get_next_led_channel()};
        set_led_supported(true);
    } else {
        ESP_LOGE(tag, "Unable to initialize LED pins.");
        set_led_supported(false);
    }
}

esp_err_t SingleLEDButton::set_led(uint32_t duty_percentage)
{
    if (!is_led_supported()) {
        return ESP_ERR_NOT_SUPPORTED;
    }

    led_.set_duty(duty_percentage);
    set_led_active(true);

    return ESP_OK;
}

} // namespace lumen::hardware
