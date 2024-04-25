#pragma once

#include "lumen/activity/field/field.hpp"
#include "lumen/hardware/display.hpp"

#include <string>
#include <vector>

namespace lumen::activity::field {

// Should only display when the timer is running
// Messages should be stored on the SD card and loaded
// Will need a way to know when to start displaying
// Will need to know which messages to display

/// TODO: Decouple advertisements from the Timer field by giving it its own
/// timer
class Advertisement : public Field<std::string> {
public:
    Advertisement(std::string const& ad);

    void set_value(std::string const& value);

    [[nodiscard]] std::string to_string() const override;

    void display(hardware::Display* display);

    [[nodiscard]] bool is_displaying() const;

private:
    // The time interval in seconds at which the advertisements should play
    uint64_t display_interval_{};
    bool is_displaying_{};

    // Will this be updated within the lifetime of the object?
    std::vector<std::string> advertisements_{};
};

} // namespace lumen::activity::field
