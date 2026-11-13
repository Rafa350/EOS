target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        UART.cpp
        UART_Types.cpp
        UART_PlatformTraits.cpp
        UART_DeviceX.cpp
        UART_Device.cpp
    PRIVATE
        UART_Device.impl.cpp
        UART_Device_Setup.impl.cpp
        UART_Device_IO.impl.cpp
        UART_Device_IO_Polling.impl.cpp
        UART_Device_IO_IRQ.impl.cpp
        UART_Device_IO_DMA.impl.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32F4")
    add_subdirectory("F4")
elseif(EOS_PLATFORM_NAME MATCHES "STM32G0")
    add_subdirectory("G0")
endif()
