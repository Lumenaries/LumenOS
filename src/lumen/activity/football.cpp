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
}

} // namespace lumen::activity
