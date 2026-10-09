target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        interrupts.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32G0")
    add_subdirectory("G0")
endif()
