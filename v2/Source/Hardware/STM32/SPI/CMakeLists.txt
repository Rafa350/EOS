target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        spi_types.cpp
        spi.cpp
        spi_class.cpp
        spi_template.cpp
        spi_platform_traits.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32F4")
    add_subdirectory("F4")
elseif(EOS_PLATFORM_NAME MATCHES "STM32G0")
    add_subdirectory("G0")
endif()
