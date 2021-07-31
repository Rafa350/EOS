#ifndef __board_Custom_SMT32F746G_DISCO__
#define __board_Custom_SMT32F746G_DISCO__


#include "Board/eosBoard_STM32F746G_DISCO.h"


#if defined(DISPLAY_ADAFRUIT_SSD1306_128x64_D098)

// Opcions generals del display
#define DISPLAY_IMAGE_WIDTH       128  // Amplada en pixels
#define DISPLAY_IMAGE_HEIGHT      64   // Alçada en pixels
#define DISPLAY_COLOR_FORMAT      ColorFormat::l1  // Format de color
#define DISPLAY_IMAGE_BUFFER      0xC0000000

// Opcions especifiques del controlador
#define DISPLAY_SSD1306_INTERFACE  DISPLAY_SSD1306_INTERFACE_SPI

#define DISPLAY_RST_PORT          ARDUINO_D0_PORT
#define DISPLAY_RST_PIN			  ARDUINO_D0_PIN

#define DISPLAY_DC_PORT           ARDUINO_D1_PORT
#define DISPLAY_DC_PIN            ARDUINO_D1_PIN

#define DISPLAY_CS_PORT           ARDUINO_D2_PORT
#define DISPLAY_CS_PIN            ARDUINO_D2_PIN

#define DISPLAY_CLK_PORT          ARDUINO_SPI_SCK_PORT
#define DISPLAY_CLK_PIN           ARDUINO_SPI_SCK_PIN
#define DISPLAY_CLK_AF			  ARDUINO_SPI_SCK_AF

#define DISPLAY_MOSI_PORT         ARDUINO_SPI_MOSI_PORT
#define DISPLAY_MOSI_PIN          ARDUINO_SPI_MOSI_PIN
#define DISPLAY_MOSI_AF           ARDUINO_SPI_MOSI_AF

#define DISPLAY_SPI_CHANNEL       HAL_SPI_CHANNEL_2


#endif


#endif // __board_Custom_STM32F746G_DISCO__

