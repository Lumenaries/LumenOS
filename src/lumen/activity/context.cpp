#include "lumen/activity/context.hpp"

#include "lumen/activity/connect.hpp"
#include "lumen/activity/football.hpp"
#include "lumen/hardware/sd_card.hpp"

#include "esp_log.h"
#include "nlohmann/json.hpp"

#include <string>

using json = nlohmann::json;

namespace lumen::activity {
namespace {

constexpr auto tag = "activity/context";

constexpr auto activity_file = "/activity.json";

/** Convert a string to an activity type.
 *
 * \param type The activity type as a string.
 *
 * \returns The equivalent `Type` enumeration of `type`.
 *
 * \returns `Type::none` if `type` could not be matched.
 */
Type str_to_type(std::string const& type);

} // namespace

Context::Context(Type type /* = Type::none */)
{
    bool loaded_activity = load_activity();

    if (!loaded_activity && type != Type::none) {
        set_activity(type);
    }
}

Activity* Context::get_activity()
{
    return activity_.get();
}

void Context::set_activity(Type type)
{
    if (activity_type_ == type) {
        return;
    }

    // TODO: Before switching to a new activity, save the state of the current
    // activity if the activity is active.

    activity_type_ = type;

    switch (type) {
    case Type::none:
        activity_.reset();
        return;

    case Type::connect:
        activity_ = std::move(std::make_unique<Connect>());
        break;

    case Type::football:
        activity_ = std::move(std::make_unique<Football>());
        break;

    default:
        ESP_LOGW(tag, "Unknown sport");
        return;
    }

    update_display();
}

Type Context::get_activity_type() const
{
    return activity_type_;
}

void Context::update_display()
{
    if (activity_ == nullptr) {
        return;
    }

    activity_->update_display();
}

void Context::button_pressed(ButtonEvent event)
{
    if (activity_ == nullptr) {
        return;
    }

    activity_->button_pressed(event);
}

void Context::store_activity()
{
    if (activity_type_ == Type::none) {
        ESP_LOGI(tag, "Activity type 'none'. Storing no information");
        return;
    }

    if (activity_type_ == Type::connect) {
        // TODO: Store the temporary activity, if it exists.
        ESP_LOGI(tag, "Activity type 'connect'. Storing no information");
        return;
    }

    hardware::write_json(activity_file, activity_->to_json());
}

bool Context::load_activity()
{
    auto activity_data = hardware::read_json(activity_file);

    if (activity_data.is_null()) {
        ESP_LOGI(tag, "No activity was previously saved");
        return false;
    }

    if (!activity_data.contains("type")) {
        ESP_LOGE(tag, "Activity save is malformed");
        hardware::delete_file(activity_file);
        return false;
    }

    auto activity_type = activity_data["type"];
    if (activity_type.is_string()) {
        set_activity(str_to_type(activity_type));
        activity_->load(activity_data);
    }

    hardware::delete_file(activity_file);
    return true;
}

namespace {

Type str_to_type(std::string const& type)
{
    if (type == "connect") {
        return Type::connect;
    }

    if (type == "football") {
        return Type::football;
    }

    // If no string matched, default to none.
    return Type::none;
}

} // namespace

} // namespace lumen::activity
