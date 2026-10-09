target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        tmr_identifiers.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32")
    add_subdirectory("STM32")
endif()
