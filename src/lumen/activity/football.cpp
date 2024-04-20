#include "lumen/activity/football.hpp"

#include "lumen/hardware/display.hpp"

#include "esp_log.h"

namespace lumen::activity {
namespace {

constexpr auto tag = "activity/football";

} // namespace

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

void Football::update_display()
{
    //auto* display = get_display();

    ESP_LOGI(
        tag,
        "Clock: %s, Score: %s",
        timer().to_string().c_str(),
        team_one().score().to_string().c_str()
    );

    // TODO: Configure how football will be displayed
}

} // namespace lumen::activity
