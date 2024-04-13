#pragma once

namespace lumen::activity {

enum class Type { none = 0, connect, football };

/// Base class from which different displayable activites should derive.
class Activity {
public:
    virtual ~Activity() = default;

    /// Defines how the derived activity should appear on the LED display.
    virtual void update_display() = 0;
};

} // namespace lumen::activity
