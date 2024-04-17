#include "lumen/net/wifi.hpp"

#include "lumen/activity/connect.hpp"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "lwip/inet.h"

#include <cstdlib>
#include <cstring>
#include <time.h>

namespace lumen::net {
namespace {

constexpr auto tag = "net/wifi";

constexpr auto esp_max_password_length = 64;

wifi_config_t config{.ap{
    .ssid = CONFIG_NET_WIFI_SSID,
    .password = CONFIG_NET_WIFI_PASSWORD,
    .ssid_len = strlen(CONFIG_NET_WIFI_SSID),
    .authmode = WIFI_AUTH_WPA_WPA2_PSK,
    .max_connection = CONFIG_NET_WIFI_MAX_STA_CONNECTION,
}};

/** Get the `Connect` activity. This should be used in callback functions.
 *
 * \param context The context of a callback function.
 */
[[nodiscard]] activity::Connect* get_connect_activity(void* context);

/// Log IP, SSID, and password information.
void log_wifi_credentials();

/// Randomize the Wi-Fi password.
void randomize_wifi_password();

/** The handler for WiFi events.
 *
 * \param context The arguments passed to the event.
 *
 * \param event_base The base ID of the event.
 *
 * \param event_id The ID of the event.
 *
 * \param event_data The data specific to the event.
 */
void wifi_event_handler(
    void* context,
    esp_event_base_t event_base,
    int32_t event_id,
    void* event_data
);

} // namespace

void init_wifi(activity::Context& activity_context)
{
    // Initialize networking stack
    ESP_ERROR_CHECK(esp_netif_init());

    // Initialize Wi-Fi including netif with default config
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&init_config));

    // WIFI_EVENT is the base ID for all events
    // ESP_EVENT_ANY_ID calls the callback function for all events that are
    // raised with the base WIFI_EVENT
    ESP_ERROR_CHECK(esp_event_handler_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, &activity_context
    ));

    if (strlen(CONFIG_NET_WIFI_PASSWORD) == 0) {
        config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(tag, "WiFi softAP initialized");
    log_wifi_credentials();
}

std::string get_wifi_password()
{
    return {reinterpret_cast<char const*>(config.ap.password)};
}

void disconnect_user()
{
    randomize_wifi_password();
    log_wifi_credentials();
}

namespace {

activity::Connect* get_connect_activity(void* context)
{
    auto* activity_context = static_cast<activity::Context*>(context);

    activity_context->set_activity(activity::Type::connect);

    return static_cast<activity::Connect*>(activity_context->get_activity());
}

void log_wifi_credentials()
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

void randomize_wifi_password()
{
    int length = CONFIG_NET_WIFI_PASSWORD_LENGTH;
    uint8_t password[esp_max_password_length] = {};

    std::srand(time(0));

    for (int i = 0; i < length; i++) {
        if (i % 2 == 0) {
            password[i] = static_cast<uint8_t>(rand() % 26 + 97);
            continue;
        }

        password[i] = password[i - 1];
    }

    std::memcpy(config.ap.password, password, esp_max_password_length);

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &config));
}

void wifi_event_handler(
    void* context,
    esp_event_base_t event_base,
    int32_t event_id,
    void* event_data
)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        auto* connect_activity = get_connect_activity(context);
        connect_activity->set_connected(true);

        auto* event = static_cast<wifi_event_ap_staconnected_t*>(event_data);
        ESP_LOGI(
            tag,
            "station " MACSTR " join, AID=%d",
            MAC2STR(event->mac),
            event->aid
        );
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        auto* connect_activity = get_connect_activity(context);

        disconnect_user();
        connect_activity->set_connected(false);

        auto* event = static_cast<wifi_event_ap_stadisconnected_t*>(event_data);
        ESP_LOGI(
            tag,
            "station " MACSTR " leave, AID=%d",
            MAC2STR(event->mac),
            event->aid
        );
    }
}

} // namespace

} // namespace lumen::net
