#include "lumen/activity/activity.hpp"

using json = nlohmann::json;

namespace lumen::activity {
namespace {

constexpr auto tag = "activity";

}

hardware::Display* Activity::get_display()
{
    return display_.get();
}

void Activity::button_pressed(ButtonEvent /* event */)
{
    ESP_LOGE(tag, "Button handler is not implemented");
}

void Activity::load(json const& /* data */)
{
    ESP_LOGE(tag, "Loading is not implemented");
}

json Activity::to_json()
{
    return {};
}

void Activity::pause()
{
    ESP_LOGE(tag, "Pause is not implemented");
}

} // namespace lumen::activity
