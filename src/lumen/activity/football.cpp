#include "lumen/activity/football.hpp"

#include "lumen/hardware/display.hpp"

using json = nlohmann::json;

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
        ESP_LOGE(tag, "Unknown button event");
        break;
    }
}

void Football::load(json data)
{
    if (data.contains("teamOne")) {
        if (data["teamOne"].contains("name") &&
            data["teamOne"]["name"].is_string()) {
            team_one_.name().set_value(data["teamOne"]["name"]);
        }

        if (data["teamOne"].contains("score") &&
            data["teamOne"]["score"].is_number_unsigned()) {
            team_one_.score().set_value(data["teamOne"]["score"]);
        }
    }

    if (data.contains("teamTwo")) {
        if (data["teamTwo"].contains("name") &&
            data["teamTwo"]["name"].is_string()) {
            team_two_.name().set_value(data["teamTwo"]["name"]);
        }

        if (data["teamTwo"].contains("score") &&
            data["teamTwo"]["score"].is_number_unsigned()) {
            team_two_.score().set_value(data["teamTwo"]["score"]);
        }
    }

    if (data.contains("quarter")) {
        auto quarter = data["quarter"];

        if (quarter.is_number_unsigned()) {
            quarter_.set_value(quarter);
        }
    }

    if (data.contains("down")) {
        auto down = data["down"];

        if (down.is_number_unsigned()) {
            down_.set_value(down);
        }
    }

    if (data.contains("yards")) {
        auto yards = data["yards"];

        if (yards.is_number_unsigned()) {
            yards_.set_value(yards);
        }
    }

    if (data.contains("timer")) {
        if (data["contains"].contains("value") &&
            data["contains"]["value"].is_number_unsigned()) {
            timer_.set_value(data["contains"]["value"]);
        }

        if (data["contains"].contains("startTime") &&
            data["contains"]["startTime"].is_number_unsigned()) {
            timer_.set_start_time(data["contains"]["startTime"]);
        }

        if (data["contains"].contains("countUp") &&
            data["contains"]["countUp"].is_boolean()) {
            timer_.set_count_up(data["contains"]["countUp"]);
        }
    }
}

json Football::to_json()
{
    return {
        {"type", "football"},
        {"teamOne",
         {{"name", team_one_.name().get_value()},
          {"score", team_one_.score().get_value()}}},
        {"teamTwo",
         {{"name", team_two_.name().get_value()},
          {"score", team_two_.score().get_value()}}},
        {"quarter", quarter_.get_value()},
        {"down", down_.get_value()},
        {"yards", yards_.get_value()},
        {"timer",
         {{"value", timer_.get_value()},
          {"startTime", timer_.get_start_time()},
          {"countUp", timer_.is_count_up()}}}
    };
}

} // namespace lumen::activity
