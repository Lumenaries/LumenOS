#pragma once

#include "lumen/activity/field/number.hpp"
#include "lumen/activity/field/text.hpp"

#include <string>

namespace lumen::activity::field {

/// A composition of different fields that represent a sports team.
class Team {
public:
    /** Team constructor.
     *
     * \param name Initial name of the team.
     */
    explicit Team(std::string const& name);

    Text& name();
    Number& score();

private:
    Text name_;
    Number score_;
};

} // namespace lumen::activity::field
