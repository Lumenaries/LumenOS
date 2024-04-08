#pragma once

#include "lumen/activity/activity.hpp"

#include <string>

namespace lumen::activity {

/// Base class from which displayable types derive.
template <typename T>
class Field {
public:
    /** Field constructor.
     *
     * \param parent Pointer to the activity object that should be updated when
     * a state change occurs.
     *
     * \param value Initial value of the field.
     */
    Field(Activity* parent, T value) : parent_{parent}, value_{value} {}
    virtual ~Field() = default;

    [[nodiscard]] T get_value() const
    {
        return value_;
    }

    /** Set the value of the field and trigger a display update.
     *
     * \param value New value of the field.
     */
    void set_value(T value)
    {
        value_ = value;
        signal_update();
    }

    /// Convert the contents of the field to a string.
    [[nodiscard]] virtual std::string to_string() const = 0;

protected:
    /// Signal the `parent` object to update the display.
    void signal_update()
    {
        if (parent_ != nullptr) {
            parent_->update_display();
        }
    }

private:
    Activity* parent_{};
    T value_{};
};


} // namespace lumen::activity
