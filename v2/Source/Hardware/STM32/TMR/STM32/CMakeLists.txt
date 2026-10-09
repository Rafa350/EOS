target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        tmr.cpp
        tmr_cls.cpp
        tmr_tpl.cpp
        tmr_traits.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32G0")
    add_subdirectory("G0B1")
endif()
