#ifndef __eosBoard_Custom_PIC32_USB_STARTER_KIT_I__
#define __eosBoard_Custom_PIC32_USB_STARTER_KIT_I__


#include "Board/eosBoard_PIC32_USB_STARTER_KIT_I.h"


// -----------------------------------------------------------------------
// Display grafic
// -----------------------------------------------------------------------

#if defined(DISPLAY_ER_TFT028_4)
#define EXIST_DISPLAY


//   ILI9341             PINGUINO      GPIO
//   -------             ----------    -------
//        10     RST     CON1-13       RD11
//        35     RD      CON1-1        RC14
//        36     WR      CON1-15       RD7
//        37     RS      CON1-2        RC13
//        38     CS      CON1-14       RD8
//               DATA    CON1-3..10    RE0..7


// Tipus de pantalla
//
#define DISPLAY_ER_TFT028_4

// Parametres de la imatge
//
#define DISPLAY_SCREEN_WIDTH      240  // Amplada en pixels
#define DISPLAY_SCREEN_HEIGHT     320  // Alçada en pixels
#define DISPLAY_COLOR_RGB565           // Codificacio de color RGB565
#define DISPLAY_IMAGE_BUFFER        0

// Parametres de controlador
//
#define DISPLAY_DRV_ILI9341            // Driver a utilitzar

// Tipus de lletra disponibles
//
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt
#define FONT_USE_Tahoma12pt

// Tipus d'interficie amb el controlador
//
#define DISPLAY_IO_TYPE_PIO8


// Control del pin RST (Reset) CON1-13
//
#define DISPLAY_RST_PORT     HAL_GPIO_PORT_D
#define DISPLAY_RST_PIN      HAL_GPIO_PIN_11

// Control del pin CS (Chip select) CON1-14
//
#define DISPLAY_CS_PORT      HAL_GPIO_PORT_D
#define DISPLAY_CS_PIN       HAL_GPIO_PIN_8

// Control del pin RS (Register select) CON1-2
//
#define DISPLAY_RS_PORT      HAL_GPIO_PORT_C
#define DISPLAY_RS_PIN       HAL_GPIO_PIN_13

// Control de pin WR (Write) D7 CON1-15
//
#define DISPLAY_WR_PORT      HAL_GPIO_PORT_D
#define DISPLAY_WR_PIN       HAL_GPIO_PIN_7

// Control del pin RD (Read) CON1-1
//
//#define DISPLAY_RD_PORT      HAL_GPIO_PORT_C
//#define DISPLAY_RD_PIN       HAL_GPIO_PIN_14

// Control del port DATA (I/O paralel port) CON1-3..10
//
#define DISPLAY_DATA_PORT    HAL_GPIO_PORT_E


#elif defined(DISPLAY_ADAFRUIT_SSD1306_128x64_D098)
#define EXISTS_DISPLAY

// Senyal     Senyal PIC32          Pin
// ---------  --------------------  -------
// SPI
// CLK
//
// 5V0        +5.0                  J10-28
// 3V3        +3.3                  J10-27
// GND        GND                   J10-45


// Parametres de la imatge
//
#define DISPLAY_SCREEN_WIDTH      240  // Amplada en pixels
#define DISPLAY_SCREEN_HEIGHT     320  // Alçada en pixels
#define DISPLAY_COLOR_FORMAT      ColorFormat::l1  // Format de color
#define DISPLAY_IMAGE_BUFFER        0


#define DISPLAY_DRV_SSD1306

#define DISPLAY_RS_PORT           HAL_GPIO_PORT_B
#define DISPLAY_RS_PIN            HAL_GPIO_PIN_4
#define DISPLAY_RS_AF             HAL_GPIO_AF_NONE

#define DISPLAY_CS_PORT           HAL_GPIO_PORT_B
#define DISPLAY_CS_PIN            HAL_GPIO_PIN_7
#define DISPLAY_CS_AF             HAL_GPIO_AF_NONE

#define DISPLAY_CLK_PORT          HAL_GPIO_PORT_F
#define DISPLAY_CLK_PIN           HAL_GPIO_PIN_7
#define DISPLAY_CLK_AF			  HAL_GPIO_AF_NONE

#define DISPLAY_MOSI_PORT         HAL_GPIO_PORT_F
#define DISPLAY_MOSI_PIN          HAL_GPIO_PIN_9
#define DISPLAY_MOSI_AF           HAL_GPIO_AF_NONE

#define DISPLAY_MISO_PORT         HAL_GPIO_PORT_F
#define DISPLAY_MISO_PIN          HAL_GPIO_PIN_8
#define DISPLAY_MISO_AF           HAL_GPIO_AF_NONE


#define DISPLAY_SPI_ID            HAL_SPI_CHANNEL_1
#endif


#endif // __eosBoard_Custom_PIC32_USB_STARTER_KIT_I__
