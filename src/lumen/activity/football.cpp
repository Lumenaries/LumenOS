#include "lumen/activity/football.hpp"

#include "lumen/hardware/display.hpp"

namespace lumen::activity {

field::Team& Football::team_one()
{
    return team_one_;
}

field::Team& Football::team_two()
{
    return team_two_;
}

field::Number& Football::quarter()
{
    return quarter_;
}

field::Number& Football::down()
{
    return down_;
}

field::Number& Football::yards()
{
    return yards_;
}

field::Timer& Football::timer()
{
    return timer_;
}

field::Advertisement& Football::advertisements()
{
    return advertisements_;
}

void Football::update_display()
{
    // TODO: Configure how football will be displayed

    // if (timer_.is_running() &&
    //     advertisements.should_display(timer_.get_value())) {
    //     ESP_LOGI(tag, "%s", advertisements.to_string());
    // }
    auto* display = get_display();

    if (timer_.is_running() &&
        advertisements_.should_display(timer_.get_value())) {
        advertisements_.display(display);
    } else {
        // Display what would usually be there
    }
}

} // namespace lumen::activity
