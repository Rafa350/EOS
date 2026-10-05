target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        clock.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        clock_HSE.impl.cpp
        clock_LSE.impl.cpp
        clock_LSI.impl.cpp
)


if(EOS_PLATFORM_NAME MATCHES "STM32F4")
	add_subdirectory("F4")
elseif(EOS_PLATFORM_NAME MATCHES "STM32G0")
	add_subdirectory("G0")
endif()
