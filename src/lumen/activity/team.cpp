#include "lumen/activity/team.hpp"

namespace lumen::activity {

Team::Team(Activity* parent, std::string const& name)
    : score_{parent}, name_{parent, name}
{
}

NumberField& Team::score()
{
    return score_;
}

TextField& Team::name()
{
    return name_;
}

} // namespace lumen::activity
