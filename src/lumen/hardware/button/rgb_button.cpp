#include "lumen/hardware/button/rgb_button.hpp"

#include "driver/ledc.h"
#include "esp_log.h"

namespace lumen::hardware::button {

RGBButton::RGBButton(
    int32_t button_pin,
    uint8_t active_level,
    int red_pin,
    int green_pin,
    int blue_pin
)
    : LEDButton{button_pin, active_level}
{
    // Check if there are enough LED channels for all LED pins.
    if (get_led_channel_count() + 3 <= static_cast<int>(LEDC_CHANNEL_MAX)) {
        red_led_ = LEDPin{red_pin, get_next_led_channel()};
        green_led_ = LEDPin{green_pin, get_next_led_channel()};
        blue_led_ = LEDPin{blue_pin, get_next_led_channel()};

        set_led_supported(true);
    } else {
        ESP_LOGE("lumen/hardware/button", "Unable to initialize LED pins.");
        set_led_supported(false);
    }
}

esp_err_t RGBButton::set_color(LEDColor color)
{
    if (!is_led_supported()) {
        return ESP_ERR_NOT_SUPPORTED;
    }

    switch (color) {
    case LEDColor::none:
        red_led_.set_duty(0);
        green_led_.set_duty(0);
        blue_led_.set_duty(0);

        set_led_active(false);
        return ESP_OK;
    case LEDColor::red:
        red_led_.set_duty(100);
        green_led_.set_duty(0);
        blue_led_.set_duty(0);
        break;
    case LEDColor::orange:
        red_led_.set_duty(75);
        green_led_.set_duty(100);
        blue_led_.set_duty(0);
        break;
    case LEDColor::yellow:
        red_led_.set_duty(50);
        green_led_.set_duty(100);
        blue_led_.set_duty(0);
        break;
    case LEDColor::green:
        red_led_.set_duty(0);
        green_led_.set_duty(100);
        blue_led_.set_duty(0);
        break;
    case LEDColor::blue:
        red_led_.set_duty(0);
        green_led_.set_duty(0);
        blue_led_.set_duty(100);
        break;
    case LEDColor::purple:
        red_led_.set_duty(25);
        green_led_.set_duty(0);
        blue_led_.set_duty(100);
        break;
    case LEDColor::white:
        red_led_.set_duty(25);
        green_led_.set_duty(50);
        blue_led_.set_duty(75);
        break;
    default:
        break;
    }

    set_led_active(true);
    return ESP_OK;
}

} // namespace lumen::hardware::button
