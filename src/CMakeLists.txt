idf_component_register(SRCS
                           "lumen/activity/context.cpp"
                           "lumen/activity/field/number.cpp"
                           "lumen/activity/field/team.cpp"
                           "lumen/activity/field/text.cpp"
                           "lumen/activity/football.cpp"
                           "lumen/app_task.cpp"
                           "lumen/net/mdns.cpp"
                           "lumen/net/wifi.cpp"
                           "lumen/web/server.cpp"
                           "main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES
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
