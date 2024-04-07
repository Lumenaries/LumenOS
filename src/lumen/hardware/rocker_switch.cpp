#include "lumen/hardware/rocker_switch.hpp"

#include "lumen/hardware/button.hpp"

#include "iot_button.h"

namespace lumen::hardware {

RockerSwitch::RockerSwitch(
    int32_t up_pin,
    uint8_t up_active_level,
    int32_t down_pin,
    uint8_t down_active_level
)
    : up_{up_pin, up_active_level}, down_{down_pin, down_active_level}
{
}

Button& RockerSwitch::up()
{
    return up_;
}

Button& RockerSwitch::down()
{
    return down_;
}

} // namespace lumen::hardware
