#ifndef __eosConfig__
#define __eosConfig__


// Opcions dels leds integrats
//
#define USE_LEDS_LED1
#define USE_LEDS_LED2

// Opcions dels switches integrats
//
#define USE_SWITCHES_SW1

// Opcions del display integrat
//
#define USE_DISPLAY
#define DISPLAY_DOUBLE_BUFFER
#define OPT_DISPLAY_DoubleBuffer

// Opcions del touchpad integrat
//
#define USE_TOUCHPAD


// Opcions del servei GUI
//
#define eosGuiService_Enabled                         1
#define eosGuiService_MessageQueueSize                10
#define eosGuiService_MessageQueueBlockTime           ((unsigned)-1)
#ifdef USE_TOUCHPAD
#define eosGuiService_TouchPadEnabled                 1
#endif

//#define eosGuiService_KeyboardEnabled                 1
#define eosGuiService_VirtualKeyboardEnabled          1

//#define OPT_GUI_Selector


#include "board/eosBoard.h"


#endif // __eosConfig__
