#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field/number.hpp"
#include "lumen/activity/field/team.hpp"
#include "lumen/activity/field/text.hpp"
#include "lumen/activity/field/timer.hpp"

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

    field::Timer& timer();

    /// Draw the fields to the display.
    void update_display() override;

private:
    field::Team team_one_{"Home"};
    field::Team team_two_{"Away"};

    field::Number quarter_{};
    field::Number down_{};
    field::Number yards_{};

    field::Timer timer_{15};
};

} // namespace lumen::activity
