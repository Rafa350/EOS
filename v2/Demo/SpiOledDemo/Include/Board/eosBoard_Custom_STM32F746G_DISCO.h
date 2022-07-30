#pragma once
#ifndef __board_Custom_SMT32F746G_DISCO__
#define __board_Custom_SMT32F746G_DISCO__


#include "Board/eosBoard_STM32F746G_DISCO.h"


#if defined(DISPLAY_ADAFRUIT_SSD1306_128x64_D098)


// Opcions generals del display
#define DISPLAY_IMAGE_WIDTH       128                 // Amplada en pixels
#define DISPLAY_IMAGE_HEIGHT      64                  // Alçada en pixels
#define DISPLAY_IMAGE_BUFFER      0xC0000000          // Buffer d'imatge

// Opcions especifiques del controlador
#define DISPLAY_SSD1306_INTERFACE  DISPLAY_SSD1306_INTERFACE_SPI


#ifdef __cplusplus

namespace board {

	namespace display {

		using GPIO_RST = board::arduino::GPIO_D0;
		using GPIO_DC = board::arduino::GPIO_D1;
		using GPIO_CS = board::arduino::GPIO_D2;
		using GPIO_SCK = board::arduino::GPIO_SCK;
		using GPIO_MOSI = board::arduino::GPIO_MOSI;
		using SPI = board::arduino::SPI;

		constexpr uint16_t width = DISPLAY_IMAGE_WIDTH;
		constexpr uint16_t height = DISPLAY_IMAGE_HEIGHT;
		constexpr uint32_t buffer = DISPLAY_IMAGE_BUFFER;
		constexpr eos::ColorFormat colorFormat = eos::ColorFormat::l1;
	}
}

#endif // __cplusplus

#endif // DISPLAY_ADAFRUIT_SSD1306_128x64_D098


#endif // __board_Custom_STM32F746G_DISCO__

