#include "lumen/activity/activity.hpp"

namespace lumen::activity {

hardware::Display* Activity::get_display()
{
    return display_.get();
}

void Activity::button_pressed(ButtonEvent event)
{
    ESP_LOGE("activity", "Button handler is not implemented");
}

} // namespace lumen::activity
