target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosDisplayDriver.cpp
        eosDisplayOrientation.cpp
        eosFrameBuffer.cpp
)

if(EOS_USE_DRIVER_ILI9341 OR
   EOS_USE_DRIVER_KS0108 OR
   EOS_USE_DRIVER_RGB OR
   EOS_USE_DRIVER_SSD1306 OR
   EOS_USE_DRIVER_ST7565)

    if(EOS_USE_DRIVER_KS0108 OR
       EOS_USE_DRIVER_SSD1306 OR
       EOS_USE_DRIVER_ST7565)
        target_sources(${TARGET_NAME} PRIVATE
            PUBLIC FILE_SET CXX_MODULES FILES
                eosL1FrameBuffer.cpp
        )

    elseif(EOS_USE_DRIVER_ILI9341 OR
           EOS_USE_DRIVER_RGB)
        target_sources(${TARGET_NAME} PRIVATE
            eosColorFrameBuffer.cpp
        )
        if (EOS_USE_HTL_DMA2D)
            target_sources(${TARGET_NAME} PRIVATE
                eosColorFrameBuffer_DMA2D.cpp
        )
        endif()
    endif()
endif()

#add_subdirectory("ILI9341")
#add_subdirectory("KS0108")
#add_subdirectory("RGB")
add_subdirectory("SSD1306")
#add_subdirectory("SSD1327")
#add_subdirectory("ST7565")
