target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        atomic.cpp
        regs.cpp
)

add_subdirectory("Clock")
add_subdirectory("Flash")

if(EOS_USE_HTL_CAN)
    add_subdirectory("CAN")
endif()

if(EOS_USE_HTL_SPI)
    add_subdirectory("SPI")
endif()

add_subdirectory("TMR")

if(EOS_USE_HTL_UART)
    add_subdirectory("UART")
endif()

add_subdirectory("DMA")
