cmake_minimum_required(VERSION 4.0)

# 
# Afegeix els fonts comuns a totes les plataformes STM32
#
target_sources(${EOS_HTL_TARGET_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/htl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlClock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlDMA.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlEXTI.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlGPIO.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlI2CMaster.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlI2CSlave.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlINT.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlSPI.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlTick.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlTMR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlUART.cpp
)


#
# Afegeix els fonts per plataformes especifiques que suportin LTDC
#
if (${PLATFORM_NAME} EQUAL "STM32F429ZI")
target_sources(${EOS_HTL_TARGET_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/htlDMA2D.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/htlLTDC.cpp
)
endif()