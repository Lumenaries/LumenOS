#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field.hpp"
#include "lumen/activity/team.hpp"

namespace lumen::activity {

/// Stores and displays the data for a Football game.
class Football : public Activity {
public:
    Football();

    /// Draw the fields to the display.
    void update_display() override;

    /// Return the first team.
    Team& team_one();

    /// Return the second team.
    Team& team_two();

    /// Return the quarter field.
    NumberField& quarter();

    /// Return the down field.
    NumberField& down();

    /// Return the yards field
    NumberField& yards();

private:
    Team team_one_;
    Team team_two_;

    NumberField quarter_;
    NumberField down_;
    NumberField yards_;
};

} // namespace lumen::activity
