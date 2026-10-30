target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        LTDC.cpp
        LTDC_Types.cpp
        LTDC_LayerTraits.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32F4")
    add_subdirectory("F4")
endif()
