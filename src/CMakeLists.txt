idf_component_register(SRCS
                           "lumen/hardware/button.cpp"
                           "lumen/hardware/button/led_button.cpp"
                           "lumen/hardware/button/rgb_button.cpp"
                           "lumen/hardware/button/rocker_switch.cpp"
                           "lumen/hardware/button/single_led_button.cpp"
                           "lumen/hardware/led_pin.cpp"
                           "lumen/net/mdns.cpp"
                           "lumen/net/wifi.cpp"
                           "lumen/web/server.cpp"
                           "main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES
                            button          # iot_button
                            driver
                            esp_event
                            esp_http_server
                            esp_hw_support  # esp_mac
                            esp_netif
                            esp_wifi
                            log             # esp_log
                            lwip
                            mdns
                            nvs_flash
                            spiffs          # esp_spiffs
                        )

set(WEB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../frontend")

if (EXISTS ${WEB_SRC_DIR}/dist)
    spiffs_create_partition_image(www ${WEB_SRC_DIR}/dist FLASH_IN_PROJECT)
else()
    message(FATAL_ERROR "${WEB_SRC_DIR}/dist doesn't exit. Please run 'npm run build' in ${WEB_SRC_DIR}")
endif()
