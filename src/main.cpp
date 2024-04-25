#include "lumen/app_task.hpp"
#include "lumen/hardware/sd_card.hpp"
#include "lumen/net/mdns.hpp"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_spiffs.h"
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

    // Initialize the SD card
    //lumen::hardware::init_sd_card();

    // Initialize the file system
    ESP_ERROR_CHECK(init_filesystem());

    // Initialize the mDNS
    lumen::net::init_mdns();

    xTaskCreate(lumen::app_task, "Application Task", 8192, nullptr, 5, nullptr);
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
