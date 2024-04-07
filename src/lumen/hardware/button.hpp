#pragma once

#include "iot_button.h"

#include <functional>
#include <list>

namespace lumen::hardware {

/// Create a button from a GPIO pin.
class Button {
public:
    /** Construct a button.
     *
     * \param button_pin The GPIO pin number of the button.
     * \param active_level The GPIO level when the button is pressed.
     */
    Button(int32_t button_pin, uint8_t active_level);

    ~Button();

    /** Register a callback function for a given button event.
     *
     * \param event The button event.
     * \param callback The callback for the button event.
     *
     * \returns ESP_OK on success.
     * \returns ESP_ERR_INVALID_ARG Arguments is invalid.
     * \returns ESP_ERR_INVALID_STATE The callback is already registered. No
     * free space for another callback.
     * \returns ESP_ERR_NO_MEM No more memory allocation for the event.
     */
    esp_err_t register_callback(button_event_t event, button_cb_t callback);

private:
    button_handle_t button_ = nullptr;
    std::list<button_event_t> registered_events_ = {};
};

} // namespace lumen::hardware
