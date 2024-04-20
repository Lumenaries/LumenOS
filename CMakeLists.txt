cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS ${CMAKE_SOURCE_DIR}/src)
set(NON_IDF_LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

if(DEFINED ENV{ARDUINO_ESP32_PATH})
    list(APPEND EXTRA_COMPONENT_DIRS $ENV{ARDUINO_ESP32_PATH})
endif()

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(lumen)
