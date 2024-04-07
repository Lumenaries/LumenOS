#pragma once

#include "lumen/hardware/button.hpp"

namespace lumen::hardware {

class LEDButton : public Button {
public:
    /** Constructor for a button with LEDs.
     *
     * \param button_pin The GPIO pin number of the button.
     * \param active_level The GPIO level when the button is pressed.
     */
    LEDButton(int32_t button_pin, uint8_t active_level);

protected:
    int get_channel_count();
    bool is_led_supported();
    bool is_led_active();

    /** Set the channel count.
     *
     * \param channel_count The number of LED channels.
     */
    void set_channel_count(int channel_count);

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
     * \Returns The next LED channel index.
     */
    int get_next_led_channel();

private:
    inline static int channel_count_ = 0;
    bool led_supported_ = false;
    bool led_active_ = false;
};

} // namespace lumen::hardware
