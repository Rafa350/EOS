#pragma once
#ifndef __board_Custom_NUCLEO_G071RB__
#define __board_Custom_NUCLEO_G071RB__


#include "Board/eosBoard_NUCLEO_G071RB.h"


// -----------------------------------------------------------------------
// OLED Display
// -----------------------------------------------------------------------
//
#ifdef USE_CUSTOM_DISPLAY
#define EXIST_DISPLAY

#define DISPLAY_INTERFACE_SPI

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


#endif // __board_Custom_NUCLEO_G071RC__

