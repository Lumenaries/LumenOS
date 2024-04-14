#include "lumen/activity/connect.hpp"

#include "lumen/net/wifi.hpp"

#include "esp_log.h"

namespace lumen::activity {
namespace {

constexpr auto tag = "activity/connect";

}

Connect::Connect()
    : ssid_{reinterpret_cast<char const*>(CONFIG_NET_WIFI_SSID)},
      mdns_hostname_{reinterpret_cast<char const*>(CONFIG_NET_MDNS_HOSTNAME)}
{
}

void Connect::set_connected(bool connected)
{
    connected_ = connected;
    update_display();
}

void Connect::update_display()
{
    if (connected_) {
        // TODO: use the display object to layout the website address.
        ESP_LOGI(tag, "website address: '%s.local'", mdns_hostname_.c_str());
        return;
    }

    // Get new password. The password will change every time a user disconnects.
    password_ = net::WiFi::get_password();

    // TODO: use the display object to layout the credentials.
    // auto* display = get_display();

    ESP_LOGI(
        tag, "SSID: '%s' password: '%s'", ssid_.c_str(), password_.c_str()
    );
}

} // namespace lumen::activity
