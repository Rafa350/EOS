add_subdirectory("Drivers")

if(EOS_USE_DRIVER_ILI9341 OR
   EOS_USE_DRIVER_KS0108 OR
   EOS_USE_DRIVER_RGB OR
   EOS_USE_DRIVER_SSD1306 OR
   EOS_USE_DRIVER_ST7565)

    target_sources(${TARGET_NAME} PRIVATE
        eosFrameBuffer.cpp
    )

    if(EOS_USE_DRIVER_KS0108 OR
       EOS_USE_DRIVER_SSD1306 OR
       EOS_USE_DRIVER_ST7565)
        target_sources(${TARGET_NAME} PRIVATE
            eosMonoFrameBuffer.cpp
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