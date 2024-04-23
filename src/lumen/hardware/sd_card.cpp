#include "lumen/hardware/sd_card.hpp"

#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

#include "driver/gpio.h"

#include <filesystem>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace lumen::hardware {

namespace {

constexpr auto tag = "hardware";

constexpr auto sd_card_mount_point = "/sdcard";

bool initialized = false;

} // namespace

void init_sd_card()
{
    esp_err_t ret;

    ESP_LOGI(tag, "Initializing SD card using the SPI peripheral");

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    auto host_slot = static_cast<spi_host_device_t>(host.slot);

    // Configure and initialize the SPI bus.

    spi_bus_config_t bus_config = {
        .mosi_io_num = CONFIG_HARDWARE_SD_CARD_MOSI_PIN,
        .miso_io_num = CONFIG_HARDWARE_SD_CARD_MISO_PIN,
        .sclk_io_num = CONFIG_HARDWARE_SD_CARD_CLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000
    };

    ret = spi_bus_initialize(host_slot, &bus_config, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        ESP_LOGE(tag, "Failed to initialize bus.");
        return;
    }

    // Configure the SD card slot without chip detection.

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.host_id = host_slot;
    slot_config.gpio_cs =
        static_cast<gpio_num_t>(CONFIG_HARDWARE_SD_CARD_CS_PIN);

    // Configure and mount the SD card.

    sdmmc_card_t* card;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5,
        .allocation_unit_size = 16 * 102
    };

    ESP_LOGI(tag, "Mounting filesystem");

    ret = esp_vfs_fat_sdspi_mount(
        static_cast<char const*>(sd_card_mount_point),
        &host,
        &slot_config,
        &mount_config,
        &card
    );

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(
                tag,
                "Failed to mount filesystem. "
                "If you want the card to be formatted, set the "
                "CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option."
            );
        } else {
            ESP_LOGE(
                tag,
                "Failed to initialize the card (%s). "
                "Make sure SD card lines have pull-up resistors in place.",
                esp_err_to_name(ret)
            );
        }
        return;
    }

    ESP_LOGI(tag, "Filesystem mounted");
    initialized = true;
    sdmmc_card_print_info(stdout, card);
}

json read_json(std::string filepath)
{
    std::ifstream file;

    file.open(sd_card_mount_point + filepath);
    if (!file) {
        ESP_LOGI(
            tag,
            "The file '%s' does not exist. Unable to read",
            filepath.c_str()
        );
        return {};
    }

    json data;
    file >> data;

    return data;
}

void write_json(std::string filepath, json data)
{
    std::ofstream file;

    file.open(sd_card_mount_point + filepath);
    if (!file.good()) {
        ESP_LOGE(tag, "Unable to write to file '%s'", filepath.c_str());
        return;
    }

    file << data;
}

void delete_file(std::string filepath)
{
    std::filesystem::remove(sd_card_mount_point + filepath);
}

} // namespace lumen::hardware
