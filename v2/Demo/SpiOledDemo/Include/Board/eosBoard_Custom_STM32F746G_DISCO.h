#pragma once
#ifndef __board_Custom_SMT32F746G_DISCO__
#define __board_Custom_SMT32F746G_DISCO__


#include "Board/eosBoard_STM32F746G_DISCO.h"


#if defined(DISPLAY_ADAFRUIT_SSD1306_128x64_D098)


// Opcions especifiques del controlador
#define DISPLAY_SSD1306_INTERFACE  DISPLAY_SSD1306_INTERFACE_SPI


#ifdef USE_CUSTOM_DISPLAY
#define EXIST_CUSTOM_DISPLAY

#define DISPLAY_RST_GPIO     ARDUINO_D0
#define DISPLAY_DC_GPIO      ARDUINO_D1
#define DISPLAY_CS_GPIO      ARDUINO_D2
#define DISPLAY_SCK_GPIO     ARDUINO_SCK
#define DISPLAY_MOSI_GPIO    ARDUINO_MOSI
#define DISPLAY_SPI          ARDUINO_SPI

#define DISPLAY_WIDTH        128
#define DISPLAY_HEIGHT       64
#define DISPLAY_BUFFER       0xC0000000

#endif // USE_CUSTOM_DISPLAY


#endif // DISPLAY_ADAFRUIT_SSD1306_128x64_D098


#endif // __board_Custom_STM32F746G_DISCO__

