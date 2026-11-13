target_sources(${TARGET_NAME}
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
        DriverISO808.cpp
    PUBLIC
        DriverISO808_Driver.impl.cpp
        DriverISO808_Device.impl.cpp
        DriverISO808_Device_Paralel.impl.cpp
        DriverISO808_Device_SPI.impl.cpp
)
