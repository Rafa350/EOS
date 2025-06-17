#pragma once
#ifndef __board_Custom_SMT32F746G_DISCO__
#define __board_Custom_SMT32F746G_DISCO__


#if defined(USE_DISPLAY) && defined(USE_CUSTOM_DISPLAY)
#error "Use only one display"
#endif


#include "Board/eosBoard_STM32F746G_DISCO.h"


// -----------------------------------------------------------------------
// LED 2
// -----------------------------------------------------------------------
//
#ifdef USE_LED2
#define EXIST_LED2

#define LED2_Pin             ARDUINO_D3_Pin
#define LED2_StateON         true
#define LED2_StateOFF        false

#endif // USE_CUSTOM_LED2


// -----------------------------------------------------------------------
// LED 3
// -----------------------------------------------------------------------
//
#ifdef USE_LED3
#define EXIST_LED3

#define LED3_Pin             ARDUINO_D2_Pin
#define LED3_StateON         true
#define LED3_StateOFF        false

#endif // USE_LED3


// -----------------------------------------------------------------------
// OLED Display
// -----------------------------------------------------------------------
//
#ifdef USE_CUSTOM_DISPLAY
#define EXIST_DISPLAY

#define DISPLAY_RST_Pin      ARDUINO_D6_Pin
#define DISPLAY_DC_Pin       ARDUINO_D5_Pin
#define DISPLAY_CS_Pin       ARDUINO_D7_Pin
#define DISPLAY_SCK_Pin      ARDUINO_SCK_Pin
#define DISPLAY_MOSI_Pin     ARDUINO_MOSI_Pin
#define DISPLAY_MISO_Pin     ARDUINO_MISO_Pin
#define DISPLAY_SPI_Device   ARDUINO_SPI_Device

#define DISPLAY_WIDTH        128
#define DISPLAY_HEIGHT       64

#endif // USE_CUSTOM_DISPLAY


#endif // __board_Custom_STM32F746G_DISCO__

