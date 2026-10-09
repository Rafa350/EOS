add_subdirectory("Clock")
add_subdirectory("Flash")
add_subdirectory("Interrupts")

if(EOS_USE_HTL_CAN)
    add_subdirectory("FDCAN")
endif()

if(EOS_USE_HTL_SPI)
    add_subdirectory("SPI")
endif()

add_subdirectory("TMR")

if(EOS_USE_HTL_UART)
    add_subdirectory("UART")
endif()

add_subdirectory("DMA")
