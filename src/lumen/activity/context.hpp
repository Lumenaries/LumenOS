#pragma once

#include "lumen/activity/activity.hpp"

#include <memory>

namespace lumen::activity {

/// The context class for displayable activities.
class Context {
public:
    explicit Context(Type type = Type::football);

    /// Get a pointer to the underlying activity.
    [[nodiscard]] Activity* get_activity() const;

    /** Set the type of the activity.
     *
     * \param type The activity type.
     */
    void set_activity(Type type);

    /// Get the current activity type.
    [[nodiscard]] Type get_activity_type() const;

    /** Redraw the display.
     *
     * Should be used when a state change occurs that should be reflected on
     * the display.
     */
    void update_display();

private:
    std::unique_ptr<Activity> activity_;

    Type activity_type_;
};

} // namespace lumen::activity
