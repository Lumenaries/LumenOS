#include "lumen/activity/field.hpp"

namespace lumen::activity {

// Field implementation.
template <typename T>
void Field<T>::signal_update()
{
    if (parent_ != nullptr) {
        parent_->update_display();
    }
}

// NumberField implementation.
NumberField::NumberField(Activity* parent, uint increment /* = 1 */)
    : Field{parent, {}}, increment_{increment}
{
}

NumberField& NumberField::increase()
{
    set_value(get_value() + increment_);

    return *this;
}

NumberField& NumberField::decrease()
{
    auto value = get_value();

    if (value >= increment_) {
        set_value(value - increment_);
    }

    return *this;
}

std::string NumberField::to_string()
{
    return std::to_string(get_value());
}

// TextField implementation.
TextField::TextField(Activity* parent, std::string const& value)
    : Field{parent, value}
{
}

bool TextField::is_scrollable() const
{
    return scrollable_;
}

void TextField::set_scrollable(bool scrollable)
{
    scrollable_ = scrollable;
}

std::string TextField::to_string()
{
    return get_value();
}

} // namespace lumen::activity
