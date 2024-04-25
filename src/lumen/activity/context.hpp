#pragma once

#include "lumen/activity/activity.hpp"

#include "nlohmann/json.hpp"

#include <memory>

namespace lumen::activity {

/// The context class for displayable activities.
class Context {
public:
    /** Context constructor.
     *
     * \param type The type of the activity to be set.
     */
    explicit Context(Type type = Type::none);

    [[nodiscard]] Activity* get_activity();

    [[nodiscard]] Type get_activity_type() const;

    /** Set the type of the activity.
     *
     * \param type The activity type.
     */
    void set_activity(Type type);

    /** Get the equivalent JSON object of the current activity.
     *
     * \returns The JSON object.
     */
    [[nodiscard]] nlohmann::json get_activity_json();

    /// Sets current activity to be the saved activity.
    void restore_activity();

    /** Redraw the display.
     *
     * Should be used when a state change occurs that should be reflected on
     * the display.
     */
    void update_display();

    /** Handler for a button press.
     *
     * \param event The button event.
     */
    void button_pressed(ButtonEvent event);

    /// Saves the current activity to the `activity_file`.
    void store_activity();

    /* Load the previously saved activity.
     *
     * \returns true if an activity was previously saved.
     *
     * \returns false if an activity was not previously saved.
     */
    bool load_activity();

private:
    std::unique_ptr<Activity> activity_{};
    Type activity_type_{};

    std::unique_ptr<Activity> saved_activity_{};
    Type saved_activity_type_{};
};

} // namespace lumen::activity
