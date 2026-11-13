add_subdirectory("Clock")
add_subdirectory("Flash")
add_subdirectory("Interrupts")

if(EOS_HARDWARE_DMA OR
   EOS_HARDWARE_CAN OR
   EOS_HARDWARE_SPI OR
   EOS_HARDWARE_I2C OR
   EOS_HARDWARE_TMR OR
   EOS_HARDWARE_UART)
    if(EOS_PLATFORM_NAME MATCHES "STM32F4" OR
       EOS_PLATFORM_NAME MATCHES "STM32F7")
        add_subdirectory("DMAs")
    else()
        add_subdirectory("DMAc")
    endif()
endif()

if(EOS_HARDWARE_GPIO OR
   EOS_HARDWARE_CAN OR
   EOS_HARDWARE_EXTI OR
   EOS_HARDWARE_SPI OR
   EOS_HARDWARE_I2C OR
   EOS_HARDWARE_TMR OR
   EOS_HARDWARE_UART OR
   EOS_HARDWARE_LTDC)
    add_subdirectory("GPIO")
endif()

if(EOS_HARDWARE_CAN)
    if(EOS_PLATFORM_NAME MATCHES "STM32G0")
        add_subdirectory("FDCAN")
    endif()
endif()

if(EOS_HARDWARE_EXTI)
    add_subdirectory("EXTI")
endif()

if(EOS_HARDWARE_SPI)
    add_subdirectory("SPI")
endif()

if(EOS_HARDWARE_I2C)
    add_subdirectory("I2C")
endif()

if(EOS_HARDWARE_TMR)
    add_subdirectory("TMR")
endif()

if(EOS_HARDWARE_UART)
    add_subdirectory("UART")
endif()

if(EOS_HARDWARE_LTDC)
    if(EOS_PLATFORM_NAME MATCHES "STM32F429" OR
       EOS_PLATFORM_NAME MATCHES "STM32F7")
        add_subdirectory("LTDC")
    endif()
endif()

if(EOS_HARDWARE_DMA2D)
    if(EOS_PLATFORM_NAME MATCHES "STM32F429" OR
       EOS_PLATFORM_NAME MATCHES "STM32F7")
        add_subdirectory("DMA2D")
    endif()
endif()
