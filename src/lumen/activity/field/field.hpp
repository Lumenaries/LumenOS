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

/// A field which represents a numeric type.
class NumberField : public Field<uint> {
public:
    /** NumberField constructor.
     *
     * \param parent Pointer to the activity object that should be updated when
     * a state change occurs.
     *
     * \param increment Interval by which the value of the field change each
     * time `increase()` or `decrease()` is called.
     */
    explicit NumberField(Activity* parent, uint increment = 1);

    /// Increase the value of the field by the value of `increment`.
    NumberField& increase();

    /// Decrease the value of the field by the value of `increment`.
    NumberField& decrease();

    /// Convert the contents of the field to a string.
    [[nodiscard]] std::string to_string() const override;

private:
    uint increment_{};
};

} // namespace lumen::activity
