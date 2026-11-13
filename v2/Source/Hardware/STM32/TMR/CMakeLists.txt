target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        TMR.cpp
        TMR_Types.cpp
        TMR_Device.cpp
        TMR_DeviceX.cpp
        TMR_DeviceTraits.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32G0")
    add_subdirectory("G0")
endif()
