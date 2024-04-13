#include "lumen/activity/football.hpp"

#include "lumen/hardware/display.hpp"

namespace lumen::activity {
namespace {

constexpr uint16_t color565(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}

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

void Football::update_display()
{
    auto* display = get_display();

    display->clearScreen();
    display->setTextColor(hardware::Display::color565(247, 141, 64));
    //display->setTextColor(color565(247, 141, 64));

    display->setCursor(70, 0);
    display->print("H:");
    display->print(team_one_.score().to_string().c_str());
}

} // namespace lumen::activity
