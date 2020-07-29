#ifndef __eosConfig__
#define __eosConfig__


#define USE_LEDS_LED1
#define USE_LEDS_LED2
#define USE_DISPLAY

//#define DISPLAY_DOUBLE_BUFFER


#include "Board/eosBoard.h"


#ifdef USE_DISPLAY
#define EXIST_DISPLAY


// Parametres de la imatge
//
#define DISPLAY_SCREEN_WIDTH      128  // Amplada en pixels
#define DISPLAY_SCREEN_HEIGHT      64  // Alçada en pixels
#define DISPLAY_COLOR_L1               // Format de color L1

// Parametres del controlador
//
#define DISPLAY_DRV_ST7565        // Driver ST7565

// Control del pin RST
//
#define DISPLAY_RST_PORT     HAL_GPIO_PORT_A
#define DISPLAY_RST_PIN      HAL_GPIO_PIN_7

// Control del pin A0
//
#define DISPLAY_A0_PORT      HAL_GPIO_PORT_A
#define DISPLAY_A0_PIN       HAL_GPIO_PIN_6

// Control del pin CS
//
#define DISPLAY_CS_PORT      HAL_GPIO_PORT_C
#define DISPLAY_CS_PIN       HAL_GPIO_PIN_2


#endif


#endif // __eosConfig__
