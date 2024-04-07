#include "lumen/activity/football.hpp"

#include "esp_log.h"

namespace lumen::activity {

Football::Football()
    : team_one_{this, "Home"}, team_two_{this, "Away"}, quarter_{this},
      down_{this}, yards_{this}
{
}

void Football::update_display()
{
    ESP_LOGI(
        "activity/football",
        "Football: update_display(): %s score: %s",
        team_one().name().to_string().c_str(),
        team_one().score().to_string().c_str()
    );
}

Team& Football::team_one()
{
    return team_one_;
}

Team& Football::team_two()
{
    return team_two_;
}

NumberField& Football::quarter()
{
    return quarter_;
}

NumberField& Football::down()
{
    return down_;
}

NumberField& Football::yards()
{
    return yards_;
}

} // namespace lumen::activity
