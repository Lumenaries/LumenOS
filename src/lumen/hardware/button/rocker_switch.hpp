#pragma once

#include "lumen/hardware/button.hpp"

namespace lumen::hardware::button {

class RockerSwitch {
public:
    /** Constructor for a rocker switch.
     *
     * \param up_pin The GPIO pin number of the up switch.
     *
     * \param up_active_level The GPIO level (high or low) when the up switch is
     * pressed. If the active level is high, input a non-zero positive. If low,
     * input 0.
     *
     * \param down_pin The GPIO pin number of the down switch.
     *
     * \param down_active_level The GPIO level (high or low) when the down switch is
     * pressed. If the active level is high, input a non-zero positive. If low,
     * input 0.
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

} // namespace lumen::hardware
