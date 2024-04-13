#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field/text.hpp"

namespace lumen::activity {

/** Stores and displays the data for a user to connect to the board.
 * This activity should be active when no user is connected.
 */
class Connect : public Activity {
public:
    Connect();

    void set_connected(bool connected);

    /// Draw the fields on the display.
    void update_display() override;

private:
    bool connected_{};
    std::string ssid_;
    std::string password_;
    std::string mdns_hostname_;
};

} // namespace lumen::activity
