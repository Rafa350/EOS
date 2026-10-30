target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        DriverSSD1306.cpp
    PUBLIC
        DriverSSD1306_Driver.impl.cpp
        DriverSSD1306_Device.impl.cpp
        DriverSSD1306_DeviceSPI.impl.cpp
        DriverSSD1306_DeviceSPIDMA.impl.cpp
)
