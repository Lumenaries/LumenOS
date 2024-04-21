#pragma once

#include "lumen/activity/activity.hpp"

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

private:
    std::unique_ptr<Activity> activity_{};
    Type activity_type_{};
};

} // namespace lumen::activity
