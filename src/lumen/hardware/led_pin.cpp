#include "lumen/hardware/led_pin.hpp"

#include "driver/ledc.h"
#include "esp_log.h"

#include <math.h>

namespace lumen::hardware {
namespace {

constexpr auto tag = "lumen/hardware";

} // namespace

LEDPin::LEDPin(int pin, int channel_num)
    : timer_config_ {
          .speed_mode = LEDC_HIGH_SPEED_MODE,
          .duty_resolution = LEDC_TIMER_2_BIT,
          .timer_num = LEDC_TIMER_0,
          .freq_hz = 4000,
          .clk_cfg = LEDC_AUTO_CLK,
      },
      channel_config_ {
        .gpio_num = pin,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = static_cast<ledc_channel_t>(channel_num),
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0,
        .flags = {},
    }
{
    duty_resolution_ = 2;
    max_duty_ = pow(2, duty_resolution_);

    ledc_timer_config(&timer_config_);
    ledc_channel_config(&channel_config_);

    set_duty(0);

    ESP_LOGI(
        tag,
        "Initialized LED pin with GPIO number %d and channel number %d.",
        pin,
        channel_num
    );
}

uint32_t LEDPin::get_duty()
{
    return ledc_get_duty(channel_config_.speed_mode, channel_config_.channel);
}

esp_err_t LEDPin::set_duty(uint32_t duty_percentage)
{
    if (duty_percentage > 100) {
        return ESP_ERR_INVALID_ARG;
    }

    // Get duty from given percentage
    auto duty = static_cast<uint8_t>(duty_percentage / 100.0 * max_duty_ + 0.5);

    ledc_set_duty(channel_config_.speed_mode, channel_config_.channel, duty);
    ledc_update_duty(channel_config_.speed_mode, channel_config_.channel);

    return ESP_OK;
}

} // namespace lumen::hardware
