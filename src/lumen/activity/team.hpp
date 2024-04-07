#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field.hpp"

#include <string>

namespace lumen::activity {

class Team {
public:
    Team(Activity* parent, std::string const& name);

    NumberField& score();
    TextField& name();

private:
    NumberField score_;
    TextField name_;
};

} // namespace lumen::activity
