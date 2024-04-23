#include "lumen/activity/field/number.hpp"

namespace lumen::activity::field {

Number::Number(uint start_value /* = 0 */, uint increment /* = 1 */)
    : Field{start_value}, start_value_{start_value}, increment_{increment}
{
}

uint Number::get_start_value()
{
    return start_value_;
}

void Number::set_start_value(uint start_value)
{
    start_value_ = start_value;
}

Number& Number::increase()
{
    set_value(get_value() + increment_);

    return *this;
}

Number& Number::decrease()
{
    auto value = get_value();

    if (value >= increment_) {
        set_value(value - increment_);
    }

    return *this;
}

std::string Number::to_string() const
{
    return std::to_string(get_value());
}

} // namespace lumen::activity::field
