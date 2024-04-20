#include "lumen/activity/field/team.hpp"

namespace lumen::activity::field {

Team::Team(std::string const& name) : name_{name}, score_{} {}

Number& Team::score()
{
    return score_;
}

Text& Team::name()
{
    return name_;
}

} // namespace lumen::activity::field
