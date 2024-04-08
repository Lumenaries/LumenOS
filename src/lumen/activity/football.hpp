#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field/number.hpp"
#include "lumen/activity/field/team.hpp"
#include "lumen/activity/field/text.hpp"

namespace lumen::activity {

/// Stores and displays the data for a Football game.
class Football : public Activity {
public:
    /// Return the first team.
    field::Team& team_one();

    /// Return the second team.
    field::Team& team_two();

    /// Return the quarter field.
    field::Number& quarter();

    /// Return the down field.
    field::Number& down();

    /// Return the yards field
    field::Number& yards();

    /// Draw the fields to the display.
    void update_display() override;

private:
    field::Team team_one_{this, "Home"};
    field::Team team_two_{this, "Away"};

    field::Number quarter_{this};
    field::Number down_{this};
    field::Number yards_{this};
};

} // namespace lumen::activity
