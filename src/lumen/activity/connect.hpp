#pragma once

#include "lumen/activity/activity.hpp"
#include "lumen/activity/field/text.hpp"

namespace lumen::activity {

/** Stores and displays the data for a user to connect to the board.
 * This activity should be active when no user is connected.
 */
class Connect : public Activity {
public:
    /* Set the connection status to the softAP.
     *
     * \param connected A value of `true` if a user successfully connected.
     * A value of `false` if a user is not connected.
     */
    void set_connected(bool connected);

    /// Draw the fields on the display.
    void update_display() override;

private:
    bool connected_{};

    std::string ssid_{CONFIG_NET_WIFI_SSID};
    std::string password_{CONFIG_NET_WIFI_PASSWORD};
    std::string mdns_hostname_{CONFIG_NET_MDNS_HOSTNAME};
};

} // namespace lumen::activity
