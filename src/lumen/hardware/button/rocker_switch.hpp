#pragma once

#include "lumen/hardware/button/button.hpp"

namespace lumen::hardware::button {

/// Defines a rocker switch composed of two separate switches.
class RockerSwitch {
public:
    /** Constructor for a rocker switch.
     *
     * \param up_pin The GPIO pin number of the up switch.
     *
     * \param up_active_level The GPIO level (high or low) when the button is
     * pressed.
     * A value of 0 will set the GPIO level to low.
     * A non-zero positive integer will set the GPIO level to high.
     *
     * \param down_pin The GPIO pin number of the down switch.
     *
     * \param down_active_level The GPIO level (high or low) when the button is
     * pressed.
     * A value of 0 will set the GPIO level to low.
     * A non-zero positive integer will set the GPIO level to high.
     */
    RockerSwitch(
        int32_t up_pin,
        uint8_t up_active_level,
        int32_t down_pin,
        uint8_t down_active_level
    );

    [[nodiscard]] Button& up();
    [[nodiscard]] Button& down();

private:
    Button up_;
    Button down_;
};

} // namespace lumen::hardware::button
