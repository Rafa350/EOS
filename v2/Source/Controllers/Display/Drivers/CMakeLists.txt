add_subdirectory("ILI9341")
add_subdirectory("SSD1306")
#add_subdirectory("SSD1327")
#add_subdirectory("ST7565")
#add_subdirectory("KS0108")

if(EOS_PLATFORM_NAME MATCHES "STM32429")
    add_subdirectory("ILI9341LTDC")
endif()

if(EOS_PLATFORM_NAME MATCHES "STM32429")
    add_subdirectory("RGBLTDC")
endif()
