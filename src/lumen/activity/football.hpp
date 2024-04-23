#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field/number.hpp"
#include "lumen/activity/field/team.hpp"
#include "lumen/activity/field/text.hpp"
#include "lumen/activity/field/timer.hpp"

#include "nlohmann/json.hpp"

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

    /// Return the timer field
    field::Timer& timer();

    /// Draw the fields to the display.
    void update_display() override;

    /** Handler for a button press.
     *
     * \param event The button event.
     */
    void button_pressed(ButtonEvent event) override;

    /** Load a saved activity.
     *
     * \param data The JSON object with the saved football data.
     */
    void load(nlohmann::json const& data) override;

    /** Constructs a JSON object from the `Football` object.
     *
     * \returns The JSON object.
     */
    nlohmann::json to_json() override;

private:
    field::Team team_one_{"Home"};
    field::Team team_two_{"Away"};

    field::Number quarter_{1};
    field::Number down_{1};
    field::Number yards_{10};

    // High school Football games have 12 minute quarters
    field::Timer timer_{12 * 60};
};

} // namespace lumen::activity
