target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        can.cpp
        can_class.cpp
        can_template.cpp
        can_device_traits.cpp
        can_platform_traits.cpp
        can_internal.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        can_class_filter.impl.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32F4")
	add_subdirectory("F4")
elseif(EOS_PLATFORM_NAME MATCHES "STM32G0")
	add_subdirectory("G0")
endif()
