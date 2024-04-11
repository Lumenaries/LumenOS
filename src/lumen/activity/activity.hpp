#pragma once

#include "lumen/hardware/display.hpp"

#include <memory>

namespace lumen::activity {

enum class Type { none = 0, football };

/// Base class from which different displayable activites should derive.
class Activity {
public:
    virtual ~Activity() = default;

    /// Defines how the derived activity should appear on the LED display.
    virtual void update_display() = 0;

protected:
    hardware::Display* get_display();

private:
    inline static auto display_ =
        std::make_unique<hardware::Display>(4, 3, 32, 16);
};

} // namespace lumen::activity
