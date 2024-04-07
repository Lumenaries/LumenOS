#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field.hpp"
#include "lumen/activity/team.hpp"

namespace lumen::activity {

class Football : public Activity {
public:
    Football();

    // Should this be protected?
    void update_display() override;

    Team& team_one();
    Team& team_two();

    NumberField& quarter();
    NumberField& down();
    NumberField& yards();

private:
    Team team_one_;
    Team team_two_;

    NumberField quarter_;
    NumberField down_;
    NumberField yards_;
};

// void test()
//{
//     auto context = get_activity_context();
//     if (context.get_activity_type() != activity::Type::Football) {
//         return;
//     }
//
//     auto football = static_cast<activity::Football>(context.get_activity());
//     football.down().increase();
//     football.team_one().score().increase();
// }

} // namespace lumen::activity
