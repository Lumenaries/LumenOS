#pragma once

#include "lumen/activity/field/field.hpp"

namespace lumen::activity::field {

/// A field which represents a numeric type.
class Number : public Field<uint> {
public:
    /** Number constructor.
     *
     * \param increment Interval by which the value of the field change each
     * time `increase()` or `decrease()` is called.
     */
    explicit Number(uint increment = 1);

    /// Increase the value of the field by the value of `increment`.
    Number& increase();

    /// Decrease the value of the field by the value of `increment`.
    Number& decrease();

    /// Convert the contents of the field to a string.
    [[nodiscard]] std::string to_string() const override;

private:
    uint increment_{};
};

} // namespace lumen::activity::field
