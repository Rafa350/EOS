target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        SPI.cpp
        SPI_Types.cpp
        spi_class.cpp
        spi_template.cpp
        SPI_PlatformTraits.cpp
)

if(EOS_PLATFORM_NAME MATCHES "STM32F4")
    add_subdirectory("F4")
elseif(EOS_PLATFORM_NAME MATCHES "STM32G0")
    add_subdirectory("G0")
endif()
