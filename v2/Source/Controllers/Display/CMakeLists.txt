target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        Display.cpp
    PUBLIC
        Display_Buffer.impl.cpp
)


if(EOS_USE_DRIVER_SSD1306 OR
   EOS_USE_DRIVER_RGBLTDC)
    add_subdirectory("Drivers")
    add_subdirectory("Buffers")
endif()
