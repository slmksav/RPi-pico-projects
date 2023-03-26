cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(project_name)

pico_sdk_init()

add_executable(template
    main.c
    header.h
)

include_directories(lib/)

# Add pico_stdlib library, add more if used
target_link_libraries(template pico_stdlib hardware_pwm hardware_timer hardware_irq hardware_adc hardware_spi hardware_i2c)

# enable usb output, disable uart output
pico_enable_stdio_usb(template 1)
pico_enable_stdio_uart(template 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(template)

