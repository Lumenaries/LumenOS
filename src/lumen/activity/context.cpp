#include "lumen/activity/context.hpp"

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
    if (activity_type_ == type) {
        return;
    }

    switch (type) {
    case Type::none:
        activity_.reset();
        break;
    case Type::football:
        activity_ = std::move(std::make_unique<activity::Football>());
        break;
    default:
        ESP_LOGW(tag, "Unknown sport");
        return;
    }

    activity_type_ = type;
}

Type Context::get_activity_type() const
{
    return activity_type_;
}

void Context::update_display()
{
    activity_->update_display();
}

} // namespace lumen::activity
