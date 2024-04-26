#include "lumen/activity/football.hpp"

#include "lumen/hardware/display.hpp"

using json = nlohmann::json;

namespace lumen::activity {
namespace {

constexpr auto tag = "activity/football";

} // namespace

Football::Football(std::map<int, std::string> const& advertisements)
    : advertisements_{20, advertisements}
{
}

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

    display->clearScreen();
    display->setTextWrap(false);
    display->setTextSize(1);

    display->setTextColor(g_secondary_color);
    display->setCursor(5, 0);
    display->print("HOME");
    display->setCursor(40, 3);
    display->print("QTR");
    display->setCursor(68, 0);
    display->print("AWAY");

    // Team One Score
    display->setTextColor(g_primary_color);
    display->setTextSize(3);
    display->setCursor(0, 9);
    // Print leading 0 if score is a single digit
    if (team_one_.score().get_value() < 10) {
        display->print("0");
    }
    display->print(team_one_.score().to_string().c_str());

    // Quarter
    display->setTextColor(g_tertiary_color);
    display->setTextSize(2);
    display->setCursor(43, 12);
    display->print(quarter_.to_string().c_str());

    // Team Two Score
    display->setTextColor(g_primary_color);
    display->setTextSize(3);
    display->setCursor(63, 9);
    // Print leading 0 if score is a single digit
    if (team_two_.score().get_value() < 10) {
        display->print("0");
    }
    display->print(team_two_.score().to_string().c_str());

    // Down
    display->setTextSize(2);
    display->setTextColor(g_secondary_color);
    display->setCursor(9, 33);
    display->print("D");
    display->setTextSize(2);
    display->setTextColor(g_tertiary_color);
    display->print(down_.to_string().c_str());

    // Yards
    display->setTextColor(g_secondary_color);
    if (yards_.get_value() < 10) {
        display->setCursor(65, 33);
    } else {
        display->setCursor(53, 33);
    }
    display->print("Y");
    display->setTextSize(2);
    display->setTextColor(g_tertiary_color);
    display->print(yards_.to_string().c_str());

    display->setTextColor(g_primary_color);
    if (timer_.is_running() &&
        advertisements_.should_display(timer_.get_value())) {
        advertisements_.display(display);
    } else {
        // Timer
        display->setCursor(19, 50);
        display->setTextSize(2);
        display->print(timer_.to_string().c_str());
    }
    display->flipDMABuffer();
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

void Football::load(json const& data)
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
        if (data["quarter"].contains("value") &&
            data["quarter"]["value"].is_number_unsigned()) {
            quarter_.set_value(data["quarter"]["value"]);
        }

        if (data["quarter"].contains("startValue") &&
            data["quarter"]["startValue"].is_number_unsigned()) {
            quarter_.set_start_value(data["quarter"]["startValue"]);
        }
    }

    if (data.contains("down")) {
        if (data["down"].contains("value") &&
            data["down"]["value"].is_number_unsigned()) {
            down_.set_value(data["down"]["value"]);
        }

        if (data["down"].contains("startValue") &&
            data["down"]["startValue"].is_number_unsigned()) {
            down_.set_start_value(data["down"]["startValue"]);
        }
    }

    if (data.contains("yards")) {
        if (data["yards"].contains("value") &&
            data["yards"]["value"].is_number_unsigned()) {
            yards_.set_value(data["yards"]["value"]);
        }

        if (data["yards"].contains("startValue") &&
            data["yards"]["startValue"].is_number_unsigned()) {
            yards_.set_start_value(data["yards"]["startValue"]);
        }
    }

    if (data.contains("timer")) {
        // Timer will always be paused after loading, so we can ignore it here

        if (data["timer"].contains("value") &&
            data["timer"]["value"].is_number_unsigned()) {
            timer_.set_value(data["timer"]["value"]);
        }

        if (data["timer"].contains("startTime") &&
            data["timer"]["startTime"].is_number_unsigned()) {
            timer_.set_start_time(data["timer"]["startTime"]);
        }

        if (data["timer"].contains("countUp") &&
            data["timer"]["countUp"].is_boolean()) {
            timer_.set_count_up(data["timer"]["countUp"]);
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
        {"quarter",
         {{"value", quarter_.get_value()},
          {"startValue", quarter_.get_start_value()}}},
        {"down",
         {{"value", down_.get_value()}, {"startValue", down_.get_start_value()}}
        },
        {"yards",
         {{"value", yards_.get_value()},
          {"startValue", yards_.get_start_value()}}},
        {"timer",
         {{"value", timer_.get_value()},
          {"startTime", timer_.get_start_time()},
          {"countUp", timer_.is_count_up()},
          {"isRunning", timer_.is_running()}}}
    };
}

void Football::pause()
{
    timer_.stop();
}

} // namespace lumen::activity
