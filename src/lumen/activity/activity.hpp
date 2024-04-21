#pragma once

#include "lumen/hardware/display.hpp"

#include <memory>

namespace lumen::activity {

enum class Type {
    none = 0,
    connect,
    football,
};

enum class ButtonEvent {
    timer = 0,
    rocker_one_up,
    rocker_one_down,
    rocker_two_up,
    rocker_two_down,
};

/// Base class from which different displayable activites should derive.
class Activity {
public:
    virtual ~Activity() = default;

    /// Defines how the derived activity should appear on the LED display.
    virtual void update_display() = 0;

    /** Handler for a button press.
     *
     * \param event The button event.
     */
    virtual void button_pressed(ButtonEvent event);

protected:
    hardware::Display* get_display();

private:
    inline static auto display_ = std::make_unique<hardware::Display>();
};

} // namespace lumen::activity
