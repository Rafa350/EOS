target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        clock.cpp
)

target_sources(${TARGET_NAME}
    PUBLIC
        clock_HSE.cpp
        clock_LSE.cpp
        clock_LSI.cpp
)


if(EOS_PLATFORM_NAME MATCHES "STM32F4")
	add_subdirectory("F4")
elseif(EOS_PLATFORM_NAME MATCHES "STM32G0")
	add_subdirectory("G0")
endif()
