target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        gpio.cpp
        gpio_types.cpp
        gpio_activator.cpp
        gpio_initializer.cpp
        gpio_utils.cpp
        gpio_platform_traits.cpp
        gpio_port_traits.cpp
        gpio_pin_traits.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        gpio.impl.cpp
)
