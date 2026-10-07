target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        uart.cpp
        uart_class.cpp
        uart_template.cpp
        uart_device_traits.cpp
        uart_platform_traits.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        uart_class.impl.cpp
        uart_class_setup.impl.cpp
        uart_class_io.impl.cpp
        uart_class_io_pol.impl.cpp
        uart_class_io_irq.impl.cpp
        uart_class_io_dma.impl.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32G0")
    add_subdirectory("G0B1")
endif()
