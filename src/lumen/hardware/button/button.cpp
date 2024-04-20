#include "lumen/hardware/button/button.hpp"

#include "driver/gpio.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_sleep.h"

namespace lumen::hardware::button {
namespace {

constexpr auto tag = "hardware/button";

} // namespace

Button::Button(int32_t button_pin, uint8_t active_level)
    : pin_{static_cast<gpio_num_t>(button_pin)}, active_level_{active_level}
{
    button_config_t config = {
        .type = BUTTON_TYPE_GPIO,
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
        .gpio_button_config =
            {
                .gpio_num = button_pin,
                .active_level = active_level,
                .enable_power_save = true,
            },
    };

    button_ = iot_button_create(&config);
    if (button_ == nullptr) {
        ESP_LOGE(tag, "Unable to create button with GPIO pin %ld.", button_pin);
    }
}

Button::~Button()
{
    // Unregister all event callbacks
    for (auto const& event : registered_events_) {
        iot_button_unregister_cb(button_, event);
    }

    iot_button_delete(button_);
}

gpio_num_t Button::get_pin() const
{
    return pin_;
}

int Button::get_active_level() const
{
    return active_level_;
}

esp_err_t Button::register_callback(
    button_event_t event,
    button_cb_t callback,
    void* context /* = nullptr */
)
{
    if (callback_context_.user_context == nullptr) {
        callback_context_.user_context = context;
    }

    // Check if a button has already been created
    if (button_ == nullptr) {
        ESP_LOGE(tag, "Button was not created.");
        return ESP_ERR_INVALID_STATE;
    }

    // Add the event
    registered_events_.push_back(event);

    return iot_button_register_cb(button_, event, callback, &callback_context_);
}

} // namespace lumen::hardware::button
