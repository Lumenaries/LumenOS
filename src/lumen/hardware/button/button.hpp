#pragma once

#include "iot_button.h"

#include <vector>

namespace lumen::hardware::button {

/// Defines a button on a GPIO pin.
class Button {
public:
    /** Button constructor.
     *
     * \param button_pin The GPIO pin number of the button.
     *
     * \param active_level The GPIO level (high or low) when the button is
     * pressed. If the active level is high, input a non-zero positive. If low,
     * input 0.
     */
    Button(int32_t button_pin, uint8_t active_level);

    virtual ~Button();

    /** Register a callback function for the given button event.
     *
     * \param event The button event.
     *
     * \param callback The callback for the button event.
     *
     * \returns ESP_OK on success.
     *
     * \returns ESP_ERR_INVALID_ARG Arguments is invalid.
     *
     * \returns ESP_ERR_INVALID_STATE The callback is already registered. No
     * free space for another callback.
     *
     * \returns ESP_ERR_NO_MEM No more memory allocation for the event.
     */
    esp_err_t register_callback(button_event_t event, button_cb_t callback, void* context = nullptr);

private:
    button_handle_t button_{};
    std::vector<button_event_t> registered_events_{};
};

} // namespace lumen::hardware::button
