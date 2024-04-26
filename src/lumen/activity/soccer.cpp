#include "lumen/activity/soccer.hpp"

using json = nlohmann::json;

namespace lumen::activity {

field::Team& Soccer::team_one()
{
    return team_one_;
}

field::Team& Soccer::team_two()
{
    return team_two_;
}

field::Number& Soccer::half()
{
    return half_;
}

field::Timer& Soccer::timer()
{
    return timer_;
}

void Soccer::update_display() {}

json Soccer::to_json()
{
    return {
        {"type", "soccer"},
        {"teamOne",
         {{"name", team_one_.name().get_value()},
          {"score", team_one_.score().get_value()}}},
        {"teamTwo",
         {{"name", team_two_.name().get_value()},
          {"score", team_two_.score().get_value()}}},
        {"half",
         {{"value", half_.get_value()},
          {"startValue", half_.get_start_value()}}},
        {"timer",
         {{"value", timer_.get_value()},
          {"startTime", timer_.get_start_time()},
          {"countUp", timer_.is_count_up()},
          {"isRunning", timer_.is_running()}}}
    };
}

} // namespace lumen::activity
