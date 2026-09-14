target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosDisplayDriver.cpp
)

#add_subdirectory("ILI9341")
#add_subdirectory("KS0108")
#add_subdirectory("RGB")
if(EOS_USE_DRIVER_SSD1306)
    add_subdirectory("SSD1306")
endif()
#add_subdirectory("SSD1327")
#add_subdirectory("ST7565")
