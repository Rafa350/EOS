target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        uart.cpp
        uart_cls.cpp
        uart_tpl.cpp
        uart_traits.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32G0")
    add_subdirectory("G0B1")
endif()
