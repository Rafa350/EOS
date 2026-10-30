target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        DriverILI9341.cpp
    PUBLIC
        DriverILI9341_Driver.impl.cpp
        DriverILI9341_Device.impl.cpp
        DriverILI9341_DeviceSPI.impl.cpp
)
