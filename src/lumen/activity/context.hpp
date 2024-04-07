#pragma once

#include "lumen/activity/activity.hpp"

#include <memory>

namespace lumen::activity {

class Context {
public:
    explicit Context(Type type = Type::football);

    Activity* get_activity();

    void set_activity(Type type);

    Type get_activity_type();

    void update_display();

private:
    std::unique_ptr<Activity> activity_;

    Type activity_type_;
};

} // namespace lumen::activity
