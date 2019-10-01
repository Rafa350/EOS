#ifndef __eosConfig__
#define __eosConfig__


#define USE_LEDS_LED1
#define USE_LEDS_LED2
#define USE_DISPLAY

//#define DISPLAY_DOUBLE_BUFFER


#include "board/board.h"


#ifdef USE_DISPLAY
#define EXIST_DISPLAY


// Parametres de la imatge
//
#define DISPLAY_SCREEN_WIDTH      240  // Amplada en pixels
#define DISPLAY_SCREEN_HEIGHT     320  // Alçada en pixels
#define DISPLAY_COLOR_L1               // Format de color L1

// Parametres del controlador
//
#define DISPLAY_DRV_ST7565        // Driver ST7565


#endif


#endif // __eosConfig__
