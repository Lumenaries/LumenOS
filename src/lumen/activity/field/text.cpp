#include "lumen/activity/field/text.hpp"

namespace lumen::activity::field {

Text::Text(Activity* parent, std::string const& value) : Field{parent, value} {}

bool Text::is_scrollable() const
{
    return scrollable_;
}

void Text::set_scrollable(bool scrollable)
{
    scrollable_ = scrollable;
}

std::string Text::to_string() const
{
    return get_value();
}

} // namespace lumen::activity::field
