#include "lumen/activity/context.hpp"

#include "lumen/activity/connect.hpp"
#include "lumen/activity/football.hpp"

#include "esp_log.h"

namespace lumen::activity {
namespace {

constexpr auto tag = "activity/context";

} // namespace

Context::Context(Type type /* = Type::none */)
{
    set_activity(type);
}

Activity* Context::get_activity()
{
    return activity_.get();
}

void Context::set_activity(Type type)
{
    // The connect activity should be "reset-able".
    if (activity_type_ != Type::connect && activity_type_ == type) {
        return;
    }

    switch (type) {
    case Type::none:
        activity_.reset();
        break;
    case Type::connect:
        ESP_LOGI(tag, "activity addr %p", activity_.get());
        activity_ = std::move(std::make_unique<Connect>());
        ESP_LOGI(tag, "activity addr %p", activity_.get());
        break;
    case Type::football:
        activity_ = std::move(std::make_unique<Football>());
        break;
    default:
        ESP_LOGW(tag, "Unknown sport");
        return;
    }

    activity_type_ = type;
    update_display();
}

Type Context::get_activity_type() const
{
    return activity_type_;
}

void Context::user_connected()
{
    if (activity_type_ != Type::connect) {
        return;
    }

    ESP_LOGI(tag, "activity addr %p", activity_.get());
    auto* connect_activity = static_cast<Connect*>(activity_.get());

    ESP_LOGI(tag, "connect activity addr set_connnected %p", connect_activity);
    connect_activity->set_connected(true);
    // connect_activity->update_display();
    // connect_activity->update_display();
}

void Context::update_display()
{
    ESP_LOGI(tag, "checking if activity is null");
    if (activity_ == nullptr) {
        return;
    }
    ESP_LOGI(tag, "activity is not null");

    activity_->update_display();
}

} // namespace lumen::activity
