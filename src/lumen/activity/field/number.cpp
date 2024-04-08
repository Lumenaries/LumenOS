#include "lumen/activity/field/number.hpp"

namespace lumen::activity::field {

Number::Number(Activity* parent, uint increment /* = 1 */)
    : Field{parent, {}}, increment_{increment}
{
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
