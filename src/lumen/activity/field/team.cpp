#include "lumen/activity/field/team.hpp"

namespace lumen::activity::field {

Team::Team(Activity* parent, std::string const& name)
    : name_{parent, name}, score_{parent}
{
}

Number& Team::score()
{
    return score_;
}

Text& Team::name()
{
    return name_;
}

} // namespace lumen::activity::field
