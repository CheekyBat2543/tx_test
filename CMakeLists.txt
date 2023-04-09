cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(tx_test)

pico_sdk_init()

add_executable(tx_test
        tx_test.cpp
)

target_link_libraries(tx_test pico_stdlib)

pico_enable_stdio_usb(tx_test 1)
pico_enable_stdio_uart(tx_test 0)

pico_add_extra_outputs(tx_test)