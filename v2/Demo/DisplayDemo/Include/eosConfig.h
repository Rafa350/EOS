#pragma once
#ifndef __eosCOnfig__
#define __eosConfig__


#if defined(HARDWARE_STM32F429I_DISC1)

    #define USE_LED1
    #define USE_LED2
    #define USE_SW1
    #define USE_DISPLAY

    #if defined(BUILD_ILI9341_SPI)

        //#define DISPLAY_ER_TFT028_4
        #define DISPLAY_DRV_ILI9341
	    #define DISPLAY_INTERFACE_SPI
        #define EOS_COLOR_FORMAT ColorFormat::rgb565

    #elif defined(BUILD_ILI9341_LTDC)

        //#define DISPLAY_ER_TFT028_4
        #define DISPLAY_DRV_ILI9341LTDC
	    #define DISPLAY_INTERFACE_RGB
        #define EOS_COLOR_FORMAT ColorFormat::rgb565

    #endif

#elif defined(HARDWARE_STM32F746G_DISCO)

    #define USE_LED1
    #define USE_SW1
    #define USE_DISPLAY
	#define DISPLAY_DRV_RGBLTDC
    #define DISPLAY_DOUBLEBUFFER false
    #define EOS_COLOR_FORMAT ColorFormat::argb8888
    //#define EOS_COLOR_FORMAT ColorFormat::rgb565
    //#define EOS_COLOR_FORMAT ColorFormat::l8

#else
    #error "Undefined HARDWARE_XXXX"
#endif


#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt
#define FONT_USE_Tahoma12pt
#define FONT_USE_Tahoma14pt


#endif // __eosConfig__
