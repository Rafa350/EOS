target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosDisplayDriver_SSD1306.cpp
    PUBLIC
        eosDisplayDriver_SSD1306_Driver.cpp
        eosDisplayDriver_SSD1306_Device.cpp
)

if(EOS_USE_HTL_SPI)
target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosDisplayDevice_SSD1306_SPI.cpp
)
endif()

if(EOS_USE_HTL_DMA AND EOS_USE_HTL_SPI)
target_sources(${TARGET_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        eosDisplayDevice_SSD1306_SPIDMA.cpp
)
endif()
