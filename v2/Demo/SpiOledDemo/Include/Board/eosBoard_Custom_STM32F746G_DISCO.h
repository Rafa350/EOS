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

#define LED1_Pin             ARDUINO_D3_Pin
#define LED1_StateON         htl::GPIOState::set
#define LED1_StateOFF        htl::GPIOState::clear

#endif // USE_CUSTOM_LED1


// -----------------------------------------------------------------------
// Led 2
// -----------------------------------------------------------------------
//
#ifdef USE_CUSTOM_LED2
#define EXIST_LED2

#define LED2_Pin             ARDUINO_D2_Pin
#define LED2_StateON         htl::GPIOState::set
#define LED2_StateOFF        htl::GPIOState::clear

#endif // USE_CUSTOM_LED2


// -----------------------------------------------------------------------
// OLED Display
// -----------------------------------------------------------------------
//
#ifdef USE_CUSTOM_DISPLAY
#define EXIST_DISPLAY

#if defined(DISPLAY_ADAFRUIT_SSD1306_128x64_D098)
#define DISPLAY_INTERFACE_SPI

#define DISPLAY_RST_Pin      ARDUINO_D6_Pin
#define DISPLAY_DC_Pin       ARDUINO_D5_Pin
#define DISPLAY_CS_Pin       ARDUINO_D7_Pin
#define DISPLAY_SCK_Pin      ARDUINO_SCK_Pin
#define DISPLAY_MOSI_Pin     ARDUINO_MOSI_Pin
#define DISPLAY_SPI_Device   ARDUINO_SPI_Device

#endif

#define DISPLAY_WIDTH        128
#define DISPLAY_HEIGHT       64
#define DISPLAY_BUFFER       0xC0000000

#endif // USE_CUSTOM_DISPLAY


#endif // __board_Custom_STM32F746G_DISCO__

