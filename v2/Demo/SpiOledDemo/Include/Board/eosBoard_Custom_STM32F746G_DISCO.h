#pragma once
#ifndef __board_Custom_SMT32F746G_DISCO__
#define __board_Custom_SMT32F746G_DISCO__


#include "Board/eosBoard_STM32F746G_DISCO.h"


// -----------------------------------------------------------------------
// Led 1
// -----------------------------------------------------------------------
//
#ifdef USE_CUSTOM_LED1
#define EXIST_LED1

#define LED1_GPIO            ARDUINO_D3
#define LED1_ON              true
#define LED1_OFF             false

#endif // USE_CUSTOM_LED1


// -----------------------------------------------------------------------
// Led 2
// -----------------------------------------------------------------------
//
#ifdef USE_CUSTOM_LED2
#define EXIST_LED2

#define LED2_GPIO            ARDUINO_D2
#define LED2_ON              true
#define LED2_OFF             false

#endif // USE_CUSTOM_LED2


// -----------------------------------------------------------------------
// OLED Display
// -----------------------------------------------------------------------
//
#ifdef USE_CUSTOM_DISPLAY
#define EXIST_DISPLAY

#if defined(DISPLAY_ADAFRUIT_SSD1306_128x64_D098)
#define DISPLAY_INTERFACE_SPI

#define DISPLAY_RST_GPIO     ARDUINO_D6
#define DISPLAY_DC_GPIO      ARDUINO_D5
#define DISPLAY_CS_GPIO      ARDUINO_D7
#define DISPLAY_SCK_GPIO     ARDUINO_SCK
#define DISPLAY_MOSI_GPIO    ARDUINO_MOSI
#define DISPLAY_SPI          ARDUINO_SPI

#endif

#define DISPLAY_WIDTH        128
#define DISPLAY_HEIGHT       64
#define DISPLAY_BUFFER       0xC0000000

#endif // USE_CUSTOM_DISPLAY


#endif // __board_Custom_STM32F746G_DISCO__

