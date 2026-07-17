# ------------------------------------------------------------------------
# Afegeix els moduls comuns
#
target_sources(${TARGET_NAME} PUBLIC 
	htl.cpp
	htlClock.cpp
	htlGPIO.cpp
	htlINT.cpp
	htlTick.cpp
)


# ------------------------------------------------------------------------
# Afegeix el modul CAN
#
if(EOS_USE_HTL_CAN)
target_sources(${TARGET_NAME} PUBLIC 
    htlCAN.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul DMA
#
if(EOS_USE_HTL_DMA)
target_sources(${TARGET_NAME} PUBLIC 
    htlDMA.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul DMA2D
#
if(EOS_USE_HTL_DMA2D)
target_sources(${TARGET_NAME} PUBLIC 
    htlDMA2D.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul DMA2D
#
if(EOS_USE_HTL_DMA2D)
target_sources(${TARGET_NAME} PUBLIC 
    htlDMA2D.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul EXTI
#
if(EOS_USE_HTL_EXTI)
target_sources(${TARGET_NAME} PUBLIC 
    htlEXTI.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul I2CMaster
#
if(EOS_USE_HTL_I2CM)
target_sources(${TARGET_NAME} PUBLIC 
    htlI2CMaster.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul I2CSlave
#
if(EOS_USE_HTL_I2CS)
target_sources(${TARGET_NAME} PUBLIC 
    htlI2CSlave.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul LTDC
#
if (EOS_USR_HTL_LTDC)
target_sources(${TARGET_NAME} PUBLIC 
	htlLTDC.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul SPI
#
if(EOS_USE_HTL_SPI)
target_sources(${TARGET_NAME} PUBLIC 
    htlSPI.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul TMR
#
if(EOS_USE_HTL_TMR)
target_sources(${TARGET_NAME} PUBLIC 
    htlTMR.cpp
)
endif()


# ------------------------------------------------------------------------
# Afegeix el modul UART
#
if(EOS_USE_HTL_UART)
target_sources(${TARGET_NAME} PUBLIC 
	htlUART.cpp
)
endif()
