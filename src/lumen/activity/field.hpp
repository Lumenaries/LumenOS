#pragma once

#include "lumen/activity/activity.hpp"

#include <string>

namespace lumen::activity {

class Activity;

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

    /// Get the current value of the field.
    [[nodiscard]] T get_value() const
    {
        return value_;
    }

    /// Set the value of the field and trigger a display update.
    void set_value(T value)
    {
        value_ = value;
        signal_update();
    }

    /// Convert the contents of the field to a string.
    virtual std::string to_string() = 0;

protected:
    /// Signal the `parent` object to update the display.
    void signal_update();

private:
    Activity* parent_;
    T value_;
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
    std::string to_string() override;

private:
    uint increment_{};
};

/// A field which represents a string type.
class TextField : public Field<std::string> {
public:
    /** NumberField constructor.
     *
     * \param parent Pointer to the activity object that should be updated when
     * a state change occurs.
     *
     * \param value Initial value that the field should hold.
     */
    TextField(Activity* parent, std::string const& value);

    /// Returns whether this field will scroll across the screen when displayed.
    [[nodiscard]] bool is_scrollable() const;

    /** Set whether is displayed as scrollable text.
     *
     * \param scrollable `true` if the text should scroll, `false` otherwise.
     */
    void set_scrollable(bool scrollable);

    // Convert the contents of the field to a string.
    std::string to_string() override;

private:
    bool scrollable_{};
};

} // namespace lumen::activity
