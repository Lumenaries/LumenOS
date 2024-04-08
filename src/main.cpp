#include "lumen/hardware/button.hpp"
#include "lumen/net/mdns.hpp"
#include "lumen/net/wifi.hpp"
#include "lumen/web/server.hpp"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_spiffs.h"
#include "esp_vfs.h"
#include "nvs_flash.h"

namespace {

constexpr auto tag = "main";

/** Initialize file system.
 * Initialize the partition for the frontend source code.
 */
esp_err_t init_filesystem();

} // namespace

extern "C" void app_main()
{
    // Create default event loop to handle system-level events
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize NVS needed by Wi-Fi
    ESP_ERROR_CHECK(nvs_flash_init());

    // Initialize the file system
    ESP_ERROR_CHECK(init_filesystem());

    lumen::net::init_wifi_softap();
    lumen::net::init_mdns();

    // TODO: Start an "Application" task that creates the web server and passes
    // it to the functions/tasks that need it.
    auto web_server = lumen::web::Server{};

    auto button = lumen::hardware::Button{25, 3};
    button.register_callback(BUTTON_SINGLE_CLICK, [](void*, void*) {
        ESP_LOGI(tag, "Button pressed");
    });

    while (true) {
        vTaskDelay(1);
    }
}

namespace {

esp_err_t init_filesystem()
{
    esp_vfs_spiffs_conf_t config = {
        .base_path = CONFIG_WEB_MOUNT_POINT,
        .partition_label = nullptr,
        .max_files = 5,
        .format_if_mount_failed = false
    };
    ESP_LOGI(tag, "%s", CONFIG_WEB_MOUNT_POINT);
    esp_err_t ret = esp_vfs_spiffs_register(&config);

    switch (ret) {
    case ESP_OK:
        break;
    case ESP_FAIL:
        ESP_LOGE(tag, "Failed to mount or format filesystem");
        break;
    case ESP_ERR_NOT_FOUND:
        ESP_LOGE(tag, "Failed to find SPIFFS partition");
        break;
    default:
        ESP_LOGE(tag, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
    }

    if (ret != ESP_OK) {
        return ESP_FAIL;
    }

    size_t total = 0;
    size_t used = 0;

    ret = esp_spiffs_info(nullptr, &total, &used);
    if (ret == ESP_OK) {
        ESP_LOGI(tag, "Partition size: total: %d, used: %d", total, used);
    } else {
        ESP_LOGE(
            tag,
            "Failed to get SPIFFS partition information (%s)",
            esp_err_to_name(ret)
        );
    }

    return ESP_OK;
}

} // namespace
