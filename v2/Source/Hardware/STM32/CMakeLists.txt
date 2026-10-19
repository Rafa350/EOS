add_subdirectory("Clock")
add_subdirectory("Flash")
add_subdirectory("Interrupts")

if(EOS_USE_DEVICE_DMA OR
   EOS_USE_DEVICE_CAN OR
   EOS_USE_DEVICE_SPI OR
   EOS_USE_DEVICE_TMR OR
   EOS_USE_DEVICE_UART)
    if(EOS_PLATFORM_NAME MATCHES "STM32F4" OR
       EOS_PLATFORM_NAME MATCHES "STM32F7")
        add_subdirectory("DMAs")
    else()
        add_subdirectory("DMAc")
    endif()
endif()

if(EOS_USE_DEVICE_GPIO OR
   EOS_USE_DEVICE_CAN OR
   EOS_USE_DEVICE_SPI OR
   EOS_USE_DEVICE_TMR OR
   EOS_USE_DEVICE_UART)
    add_subdirectory("GPIO")
endif()

if(EOS_USE_DEVICE_CAN)
    add_subdirectory("FDCAN")
endif()

if(EOS_USE_DEVICE_EXTI)
    add_subdirectory("EXTI")
endif()

if(EOS_USE_DEVICE_SPI)
    add_subdirectory("SPI")
endif()

if(EOS_USE_DEVICE_TMR)
    add_subdirectory("TMR")
endif()

if(EOS_USE_DEVICE_UART)
    add_subdirectory("UART")
endif()
