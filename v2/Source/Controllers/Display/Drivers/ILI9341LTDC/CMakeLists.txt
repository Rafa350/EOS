target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        DriverILI9341LTDC.cpp
    PUBLIC
        DriverILI9341LTDC_Driver.impl.cpp
)
