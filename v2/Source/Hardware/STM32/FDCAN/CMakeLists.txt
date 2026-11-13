target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        FDCAN.cpp
        FDCAN_Device.cpp
        FDCAN_DeviceX.cpp
        FDCAN_DeviceTraits.cpp
        FDCAN_PlatformTraits.cpp
        FDCAN_Types.cpp
        FDCAN_Internal.cpp
    PUBLIC
        FDCAN_Device_Filter.impl.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32G0")
	add_subdirectory("G0")
endif()
