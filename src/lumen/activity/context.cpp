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
    if (type != Type::none) {
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

} // namespace lumen::activity
