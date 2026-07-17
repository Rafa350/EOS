# ------------------------------------------------------------------------
# Afegeix muduls base del driver
#
target_sources(${TARGET_NAME} PRIVATE
    eosDevice_SSD1306.cpp
    eosDisplayDriver_SSD1306.cpp
)


# ------------------------------------------------------------------------
# Afegeix muduls d'interficie SPI
#
if(EOS_USE_HTL_SPI)
target_sources(${TARGET_NAME} PRIVATE
    eosDevice_SSD1306_SPI.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix muduls d'interficie SPI per DMA
#
if(EOS_USE_HTL_DMA AND EOS_USE_HTL_SPI)
target_sources(${TARGET_NAME} PRIVATE
    eosDevice_SSD1306_SPIDMA.cpp
)
endif()

