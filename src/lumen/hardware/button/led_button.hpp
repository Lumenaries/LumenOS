#pragma once

#include "lumen/hardware/button.hpp"

namespace lumen::hardware::button {

/// Defines a button with LEDs.
class LEDButton : public Button {
public:
    /** LEDButton constructor.
     *
     * \param button_pin The GPIO pin number of the button.
     *
     * \param active_level The GPIO level (high or low) when the button is
     * pressed. If the active level is high, input a non-zero positive. If low,
     * input 0.
     */
    LEDButton(int32_t button_pin, uint8_t active_level);

protected:
    [[nodiscard]] int get_led_channel_count() const;

    [[nodiscard]] bool is_led_supported() const;

    [[nodiscard]] bool is_led_active() const;

    /** Set the button's LED support.
     *
     * \param led_support If the button supports LEDs.
     */
    void set_led_supported(bool led_supported);

    /** Set state of the button's LEDs.
     *
     * \param led_active If the button's LEDs are active.
     */
    void set_led_active(bool led_active);

    /* Gets the next LED channel index and increments the channel count.
     *
     * \returns The index of the next LED channel.
     */
    [[nodiscard]] int get_next_led_channel();

private:
    inline static int led_channel_count_{};

    bool led_supported_{};
    bool led_active_{};
};

} // namespace lumen::hardware
