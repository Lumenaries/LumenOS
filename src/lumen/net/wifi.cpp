#include "lumen/net/wifi.hpp"

#include "lumen/activity/connect.hpp"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_netif.h"
#include "lwip/inet.h"

#include <cstdlib>
#include <cstring>
#include <time.h>

namespace lumen::net {
namespace {

constexpr auto tag = "net/wifi";

wifi_config_t config{.ap{
    .ssid = CONFIG_NET_WIFI_SSID,
    .password = CONFIG_NET_WIFI_PASSWORD,
    .ssid_len = strlen(CONFIG_NET_WIFI_SSID),
    .authmode = WIFI_AUTH_WPA_WPA2_PSK,
    .max_connection = CONFIG_NET_WIFI_MAX_STA_CONNECTION,
}};

/** The handler for WiFi events.
 *
 * \param arg The arguments passed to the event.
 * \param event_base The base ID of the event.
 * \param event_id The ID of the event.
 * \param event_data The data specific to the event.
 */
void wifi_event_handler(
    void* arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void* event_data
);

} // namespace

WiFi::WiFi()
{
    // Initialize networking stack
    ESP_ERROR_CHECK(esp_netif_init());

    // Initialize Wi-Fi including netif with default config
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&init_config));

    if (strlen(CONFIG_NET_WIFI_PASSWORD) == 0) {
        config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(tag, "WiFi softAP initialized");
    log_credentials();
}

void WiFi::register_callback(CallbackContext& callback_context)
{
    // WIFI_EVENT is the base ID for all events
    // ESP_EVENT_ANY_ID calls the callback function for all events that are
    // raised with the base WIFI_EVENT
    ESP_ERROR_CHECK(esp_event_handler_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, &callback_context
    ));

    ESP_LOGI(tag, "Registered WiFi event handler");
}

std::string WiFi::get_password()
{
    return {reinterpret_cast<char const*>(config.ap.password)};
}

void WiFi::reset()
{
    randomize_password();
    log_credentials();
}

void WiFi::randomize_password()
{
    int length = CONFIG_NET_WIFI_PASSWORD_LENGTH;
    uint8_t password[length];

    std::srand(time(0));
    for (int i = 0; i < length; i++) {
        password[i] = static_cast<uint8_t>(rand() % 26 + 97);
    }

    std::memcpy(config.ap.password, password, length);

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &config));

    ESP_LOGI(tag, "Randomize softAP password");
}

void WiFi::log_credentials()
{
    esp_netif_ip_info_t ip_info;
    esp_netif_get_ip_info(
        esp_netif_get_handle_from_ifkey("WIFI_AP_DEF"), &ip_info
    );

    char ip_addr[16];
    inet_ntoa_r(ip_info.ip.addr, ip_addr, 16);
    ESP_LOGI(tag, "Set up softAP with IP: %s", ip_addr);

    ESP_LOGI(
        tag, "SSID: '%s' password: '%s'", config.ap.ssid, config.ap.password
    );
}

namespace {

void wifi_event_handler(
    void* callback_context,
    esp_event_base_t event_base,
    int32_t event_id,
    void* event_data
)
{
    auto* context = static_cast<CallbackContext*>(callback_context);
    auto* activity_context = context->activity_context;
    auto* wifi = context->wifi;

    if (activity_context->get_activity_type() == activity::Type::connect) {
        auto* connect_activity = static_cast<activity::Connect*>(
            context->activity_context->get_activity()
        );

        if (event_id == WIFI_EVENT_AP_STACONNECTED) {
            auto* event =
                static_cast<wifi_event_ap_staconnected_t*>(event_data);
            ESP_LOGI(
                tag,
                "station " MACSTR " join, AID=%d",
                MAC2STR(event->mac),
                event->aid
            );

            connect_activity->set_connected(true);
        } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
            auto* event =
                static_cast<wifi_event_ap_stadisconnected_t*>(event_data);
            ESP_LOGI(
                tag,
                "station " MACSTR " leave, AID=%d",
                MAC2STR(event->mac),
                event->aid
            );

            wifi->reset();
            connect_activity->set_connected(false);
        }
    }
}

} // namespace

} // namespace lumen::net
