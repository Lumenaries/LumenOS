#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field.hpp"

#include <string>

namespace lumen::activity {

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

    /// Return the score field.
    NumberField& score();

    /// Return the name field.
    TextField& name();

private:
    NumberField score_;
    TextField name_;
};

} // namespace lumen::activity
