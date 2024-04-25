idf_component_register(SRCS
                           "lumen/activity/activity.cpp"
                           "lumen/activity/connect.cpp"
                           "lumen/activity/context.cpp"
                           "lumen/activity/field/number.cpp"
                           "lumen/activity/field/team.cpp"
                           "lumen/activity/field/text.cpp"
                           "lumen/activity/field/timer.cpp"
                           "lumen/activity/football.cpp"
                           "lumen/app_task.cpp"
                           "lumen/button_callback.cpp"
                           "lumen/hardware/button/button.cpp"
                           "lumen/hardware/button/led_button.cpp"
                           "lumen/hardware/button/rg_led_button.cpp"
                           "lumen/hardware/button/rocker_switch.cpp"
                           "lumen/hardware/display.cpp"
                           "lumen/hardware/led_pin.cpp"
                           "lumen/hardware/sd_card.cpp"
                           "lumen/net/mdns.cpp"
                           "lumen/net/wifi.cpp"
                           "lumen/web/error.cpp"
                           "lumen/web/handler/common.cpp"
                           "lumen/web/handler/event.cpp"
                           "lumen/web/handler/football.cpp"
                           "lumen/web/server.cpp"
                           "main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES
                            # Third-party libraries.
                            ESP32-HUB75-MatrixPanel-DMA

                            # First-party libraries.
                            button          # iot_button
                            driver
                            esp_event
                            esp_http_server
                            esp_hw_support  # esp_mac
                            esp_netif
                            esp_wifi
                            fatfs           # esp_vfs_fat
                            log             # esp_log
                            lwip
                            mdns
                            nvs_flash
                            spiffs          # esp_spiffs
                        )

# Save website to storage device
set(WEB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../frontend")

if (EXISTS ${WEB_SRC_DIR}/dist)
    spiffs_create_partition_image(www ${WEB_SRC_DIR}/dist FLASH_IN_PROJECT)
else()
    message(FATAL_ERROR "${WEB_SRC_DIR}/dist doesn't exit. Please run 'npm install; npm run build' in ${WEB_SRC_DIR}")
endif()

# Third party non-component libraries.

# nlohmann/json
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")

# Add json library as a subdirectory and build it in "build/json"
add_subdirectory(${NON_COMPONENT_LIB_DIR}/json ${CMAKE_BINARY_DIR}/json)
target_link_libraries(${COMPONENT_LIB} PUBLIC nlohmann_json::nlohmann_json)
