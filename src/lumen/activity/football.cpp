#include "lumen/activity/football.hpp"

#include "esp_log.h"

namespace lumen::activity {

void Football::update_display()
{
    ESP_LOGI(
        "activity/football",
        "Football: update_display(): %s score: %s",
        team_one().name().to_string().c_str(),
        team_one().score().to_string().c_str()
    );
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

} // namespace lumen::activity
