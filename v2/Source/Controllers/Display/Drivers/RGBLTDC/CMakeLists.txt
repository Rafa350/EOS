target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        DriverRGBLTDC.cpp
    PUBLIC
        DriverRGBLTDC_Device.impl.cpp
)
