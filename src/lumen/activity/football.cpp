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
    // TODO: Configure how football will be displayed
    auto* display = get_display();

    display->setCursor(0, 0);
    display->print("H:");
    display->print(team_one().score().to_string().c_str());
    ESP_LOGI(tag, "HOME: %d", team_one().score().get_value());

    display->print("  ");
    display->print("A:");
    display->println(team_two().score().to_string().c_str());
    ESP_LOGI(tag, "AWAY: %d", team_two().score().get_value());

    display->print("  ");
    display->print("Q:");
    display->print(quarter().to_string().c_str());
    ESP_LOGI(tag, "QUARTER: %d", quarter().get_value());

    display->print("  ");
    display->print("D:");
    display->print(down().to_string().c_str());
    ESP_LOGI(tag, "DOWN: %d", down().get_value());

    display->print("  ");
    display->print("Y:");
    display->println(yards().to_string().c_str());
    ESP_LOGI(tag, "YARDS: %d", yards().get_value());

    display->print(timer().to_string().c_str());
    ESP_LOGI(tag, "TIME: %s", timer().to_string().c_str());
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
