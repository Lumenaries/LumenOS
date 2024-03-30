#include "lumen/activity/snapshot.hpp"

#include "esp_log.h"

namespace lumen::activity {
namespace {

constexpr auto bg_color = 52825;
constexpr auto primary_color = 62568;

} // namespace

Snapshot::Snapshot(Display* display) : display_{display}
{
    update_display();
}

void Snapshot::reset()
{
    auto reset_condition = home_ + away_;

    home_ = 0;
    away_ = 0;

    if (reset_condition > 0) {
        update_display();
    }
}

void Snapshot::increase_score(Team team)
{
    if (team == Team::home) {
        home_++;
    } else {
        away_++;
    }

    update_display();
}

void Snapshot::decrease_score(Team team)
{
    if (team == Team::home && home_ > 0) {
        home_--;
    } else if (team == Team::away && away_ > 0) {
        away_--;
    } else {
        // No need to refresh the display
        return;
    }

    update_display();
}

void Snapshot::update_display()
{
    display_->clearScreen();

    display_->setTextSize(2);

    display_->setTextColor(primary_color);

    // display_->setCursor(0, 0);
    // display_->print(std::to_string(home_).c_str());

    // display_->setCursor(20, 0);
    // display_->print(std::to_string(away_).c_str());

    display_->setTextWrap(false);

    // "HOME"
    display_->setCursor(8, 9);
    display_->print("HOME:");

    // "AWAY"
    display_->setCursor(8, 35);
    display_->print("AWAY:");

    display_->setTextColor(bg_color);

    // Home score
    display_->setCursor(68, 9);
    display_->print(std::to_string(home_).c_str());

    display_->setCursor(68, 35);
    display_->print(std::to_string(away_).c_str());
}

} // namespace lumen::activity
