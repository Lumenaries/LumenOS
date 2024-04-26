#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field/number.hpp"
#include "lumen/activity/field/team.hpp"
#include "lumen/activity/field/timer.hpp"

#include "nlohmann/json.hpp"

namespace lumen::activity {

/// Stores and displays the data for a Soccer game.
class Soccer : public Activity {
public:
    /// Return the first team.
    field::Team& team_one();

    /// Return the second team.
    field::Team& team_two();

    /// Return the quarter field.
    field::Number& half();

    /// Return the timer field
    field::Timer& timer();

    /// Draw the fields to the display.
    void update_display() override;

    /** Constructs a JSON object from the `Soccer` object.
     *
     * \returns The JSON object.
     */
    nlohmann::json to_json() override;

private:
    field::Team team_one_{"Home"};
    field::Team team_two_{"Away"};

    field::Number half_{1};

    // Soccer games typically have 45 minute halves.
    field::Timer timer_{45 * 60};
};

} // namespace lumen::activity
