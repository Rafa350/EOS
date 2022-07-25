#ifndef __eosConfig__
#define __eosConfig__


// Opcions generals del sistema
//
#define EOS_USE_STD_STRING


// Opcions dels leds integrats
//
#define USE_LED1
#define USE_LED2

// Opcions dels switches integrats
//
#define USE_SW1

// Opcions del display integrat
//
#define USE_DISPLAY
#define DISPLAY_DRV_RGBLTDC
#define DISPLAY_COLOR_FORMAT                          eos::ColorFormat::rgb565
#define DISPLAY_DOUBLEBUFFER                          true
#define OPT_DISPLAY_DoubleBuffer
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt
#define FONT_USE_Tahoma10pt
#define FONT_USE_Tahoma12pt

// Opcions del touchpad integrat
//
#define USE_TOUCHPAD


// Opcions del servei GUI
//
#define eosGuiService_Enabled                         1
#define eosGuiService_MessageQueueSize                10
#define eosGuiService_MessageQueueBlockTime           ((unsigned)-1)
#ifdef USE_TOUCHPAD
#define eosGuiService_TouchpadEnabled                 1
#endif

//#define eosGuiService_KeyboardEnabled                 1
#define eosGuiService_VirtualKeyboardEnabled          1

//#define OPT_GUI_Selector

#endif // __eosConfig__
