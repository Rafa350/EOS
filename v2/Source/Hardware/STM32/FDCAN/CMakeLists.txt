target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        fdcan.cpp
        fdcan_class.cpp
        fdcan_template.cpp
        fdcan_device_traits.cpp
        fdcan_platform_traits.cpp
        fdcan_internal.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        fdcan_class_filter.impl.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32G0")
	add_subdirectory("G0")
endif()
