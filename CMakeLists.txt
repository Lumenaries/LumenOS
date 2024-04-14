cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS src lib)

if(DEFINED ENV{ARDUINO_ESP32_PATH})
    list(APPEND EXTRA_COMPONENT_DIRS $ENV{ARDUINO_ESP32_PATH})
endif()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(lumen)
