#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field/number.hpp"
#include "lumen/activity/field/text.hpp"

#include <string>

namespace lumen::activity::field {

/// A composition of different fields that represent a sports team.
class Team {
public:
    /** Team constructor.
     *
     * \param parent Pointer to the activity object that should be updated when
     * a state change occurs.
     *
     * \param name Initial name of the team.
     */
    Team(Activity* parent, std::string const& name);

    Text& name();
    Number& score();

private:
    Text name_;
    Number score_;
};

} // namespace lumen::activity::field
