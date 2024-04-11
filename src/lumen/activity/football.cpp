#include "lumen/activity/football.hpp"

namespace lumen::activity {

Football::Football()
{
    update_display();
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

void Football::update_display()
{
    auto* display = get_display();

    display->clearScreen();

    display->setCursor(0, 0);
    display->print(team_one_.score().to_string().c_str());
}

} // namespace lumen::activity
