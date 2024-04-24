#pragma once

#include "lumen/activity/field/field.hpp"

namespace lumen::activity::field {

/// A field which represents a numeric type.
class Number : public Field<uint> {
public:
    /** Number constructor.
     *
     * \param start_value The starting value of the field.
     *
     * \param increment Interval by which the value of the field change each
     * time `increase()` or `decrease()` is called.
     */
    explicit Number(uint start_value = 0, uint increment = 1);

    [[nodiscard]] uint get_start_value() const;

    /** Set the starting value of the field.
     *
     * \param start_value The starting value of the field.
     */
    void set_start_value(uint start_value);

    /// Increase the value of the field by the value of `increment`.
    Number& increase();

    /// Decrease the value of the field by the value of `increment`.
    Number& decrease();

    /// Convert the contents of the field to a string.
    [[nodiscard]] std::string to_string() const override;

private:
    uint start_value_{};
    uint increment_{};
};

} // namespace lumen::activity::field
