#ifndef __eosConfig__
#define __eosConfig__


// Opcions dels leds integrats
//
#define USE_LEDS_LED1
#define USE_LEDS_LED2

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
#ifdef USE_TOUCHPAD
#define OPT_GUI_TouchPad
#endif

//#define OPT_GUI_Keyboard

//#define OPT_GUI_Selector

#define OPT_GUI_MessageQueueSize                 10
#define OPT_GUI_MessageQueueBlockTime            ((unsigned)-1)


#include "board/board.h"


#endif // __eosConfig__
