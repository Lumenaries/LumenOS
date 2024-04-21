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

void Football::update_display()
{
    // TODO: Configure how football will be displayed
    ESP_LOGI("activity/football", "Timer: %s", timer_.to_string().c_str());
    ESP_LOGI(
        "activity/football",
        "Team one score: %s",
        team_one_.score().to_string().c_str()
    );
    ESP_LOGI(
        "activity/football",
        "Team two score: %s",
        team_two_.score().to_string().c_str()
    );
}

void Football::button_pressed(ButtonEvent event)
{
    switch (event) {
    case ButtonEvent::timer:
        timer_.toggle();
        break;
    case ButtonEvent::rocker_one_up:
        team_one_.score().increase();
        break;
    case ButtonEvent::rocker_one_down:
        team_one_.score().decrease();
        break;
    case ButtonEvent::rocker_two_up:
        team_two_.score().increase();
        break;
    case ButtonEvent::rocker_two_down:
        team_two_.score().decrease();
        break;
    default:
        ESP_LOGE("activity/football", "Unknown button event");
        break;
    }
}

} // namespace lumen::activity
