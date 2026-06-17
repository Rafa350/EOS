# 
# Afegeix els fonts comuns a totes les plataformes STM32
#
target_sources(${TARGET_NAME} PUBLIC 
	htl.cpp
    htlCAN.cpp
	htlClock.cpp
	htlDMA.cpp
	htlEXTI.cpp
	htlGPIO.cpp
	htlI2CMaster.cpp
	htlI2CSlave.cpp
	htlINT.cpp
	htlSPI.cpp
	htlTick.cpp
	htlTMR.cpp
	htlUART.cpp
)


#
# Afegeix els fonts per plataformes especifiques que suportin LTDC
#
if (EOS_PLATFORM_NAME EQUAL "STM32F429ZI")
target_sources(${TARGET_NAME} PUBLIC 
	htlDMA2D.cpp
	htlLTDC.cpp
)
endif()