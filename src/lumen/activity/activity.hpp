#pragma once

//  #include "lumen/activity/display.hpp"

namespace lumen::activity {

enum class Type { None, Football };

class Activity {
public:
    virtual ~Activity() = default;

    virtual void update_display() = 0;

protected:
    // static Display* get_display();

private:
    // inline static auto display_ = std::make_unique<Display>();
};

} // namespace lumen::activity
