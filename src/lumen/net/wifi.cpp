#include "lumen/net/wifi.hpp"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "lwip/inet.h"

#include <cstring>

namespace lumen::net {
namespace {

constexpr auto tag = "net/wifi";

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

void init_wifi_softap()
{
    // Initialize networking stack
    ESP_ERROR_CHECK(esp_netif_init());

    // Initialize Wi-Fi including netif with default config
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));

    // WIFI_EVENT is the base ID for all events
    // ESP_EVENT_ANY_ID calls the callback function for all events that are
    // raised with the base WIFI_EVENT
    ESP_ERROR_CHECK(esp_event_handler_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL
    ));

    wifi_config_t wifi_config = {
        .ap =
            {.ssid = CONFIG_NET_WIFI_SSID,
             .password = CONFIG_NET_WIFI_PASSWORD,
             .ssid_len = strlen(CONFIG_NET_WIFI_SSID),
             .authmode = WIFI_AUTH_WPA_WPA2_PSK,
             .max_connection = CONFIG_NET_WIFI_MAX_STA_CONNECTION}
    };

    if (strlen(CONFIG_NET_WIFI_PASSWORD) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    esp_netif_ip_info_t ip_info;
    esp_netif_get_ip_info(
        esp_netif_get_handle_from_ifkey("WIFI_AP_DEF"), &ip_info
    );

    char ip_addr[16];
    inet_ntoa_r(ip_info.ip.addr, ip_addr, 16);
    ESP_LOGI(tag, "Set up softAP with IP: %s", ip_addr);

    ESP_LOGI(
        tag,
        "wifi_init_softap finished. SSID:'%s' password:'%s'",
        CONFIG_NET_WIFI_SSID,
        CONFIG_NET_WIFI_PASSWORD
    );
}

namespace {

void wifi_event_handler(
    void* arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void* event_data
)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        // TODO: This will signal when we can display the website link
        // instead of the SSID and password
        auto* event = static_cast<wifi_event_ap_staconnected_t*>(event_data);
        ESP_LOGI(
            tag,
            "station " MACSTR " join, AID=%d",
            MAC2STR(event->mac),
            event->aid
        );
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
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
