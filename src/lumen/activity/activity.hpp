#pragma once

#include "lumen/hardware/display.hpp"

#include "nlohmann/json.hpp"

#include <memory>

namespace lumen::activity {

// White
constexpr auto g_primary_color = hardware::Display::color565(200, 200, 200);
// Dark Orange
constexpr auto g_secondary_color = hardware::Display::color565(255, 128, 0);
// Light Orange
constexpr auto g_tertiary_color = hardware::Display::color565(255, 163, 71);

enum class Type {
    none = 0,
    connect,
    football,
    soccer,
};

enum class ButtonEvent {
    timer = 0,
    rocker_one_up,
    rocker_one_down,
    rocker_two_up,
    rocker_two_down,
};

/// Base class from which different displayable activites should derive.
class Activity {
public:
    virtual ~Activity() = default;

    /// Defines how the derived activity should appear on the LED display.
    virtual void update_display() = 0;

    /** Handler for a button press.
     *
     * \param event The button event.
     */
    virtual void button_pressed(ButtonEvent event);

    /** Load a saved activity.
     *
     * \param data The JSON object with the saved activity data.
     */
    virtual void load(nlohmann::json const& data);

    /** Constructs a JSON object from the `Activity` object.
     *
     * \returns The JSON object.
     */
    virtual nlohmann::json to_json();

    /** Pause the activity.
     *
     * What actually happens depends on the activity, but
     * it could be as simple as pausing a field::Timer.
     */
    virtual void pause();

protected:
    hardware::Display* get_display();

private:
    inline static auto display_ = std::make_unique<hardware::Display>();
};

} // namespace lumen::activity
