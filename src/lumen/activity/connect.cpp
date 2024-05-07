#include "lumen/activity/connect.hpp"

#include "lumen/app_task.hpp"
#include "lumen/net/wifi.hpp"

#include "esp_log.h"

namespace lumen::activity {
namespace {

constexpr auto tag = "activity/connect";

} // namespace

void Connect::set_connected(bool connected)
{
    if (connected_ != connected) {
        connected_ = connected;
    }

    update_display();
}

void Connect::update_display()
{
    auto* display = get_display();

    display->clearScreen();
    display->setTextColor(g_secondary_color);
    display->setTextSize(1);
    display->setCursor(15, 10);
    display->println("Connect!");

    display->setTextColor(g_tertiary_color);
    if (connected_) {
        display->setCursor(10, 23);
        display->print("'");
        display->print(mdns_hostname_.c_str());
        display->print(".local'");

        ESP_LOGI(tag, "website address: '%s.local'", mdns_hostname_.c_str());
    } else {
        // Get new password. The password will change every time a user
        // disconnects.
        password_ = net::get_wifi_password();

        display->setCursor(20, 25);
        display->print(ssid_.c_str());

        display->setCursor(20, 35);
        display->print(password_.c_str());

        ESP_LOGI(
            tag, "SSID: '%s' password: '%s'", ssid_.c_str(), password_.c_str()
        );
    }

    display->flipDMABuffer();
}

void Connect::button_pressed(ButtonEvent)
{
    signal_update(g_swap_to_default_activity);
}

} // namespace lumen::activity
