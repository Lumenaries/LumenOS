#include "lumen/activity/activity.hpp"

namespace lumen::activity {

hardware::Display* Activity::get_display()
{
    return display_.get();
}

} // namespace lumen::activity
