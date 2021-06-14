#ifndef __eosConfig__
#define __eosConfig__


#if defined(BUILD_ILI9341_SPI)
#if defined(EOS_STM32F4)
#define HARDWARE_STM32F429I_DISC1
#elif defined(EOS_STM32F7)
#define HARDWARE_STM32F746G_DISCO
#elif defined(EOS_PIC32)
#define HARDWARE_CUSTOM
#define HARDWARE_CUSTOM_PIC32_USR_STARTER_KIT_I
#define DISPLAY_ER_TFT028_4
#else
#error "Hardware no soportado para ILI9341-SPI "
#endif
#define USE_DISPLAY
#define DISPLAY_DRV_ILI9341

#elif defined(BUILD_ILI9341_LTDC)
#if defined(EOS_STM32F4)
#define HARDWARE_STM32F429I_DISC1
#elif defined(EOS_STM32F7)
#define HARDWARE_STM32F746G_DISCO
#else
#error "Hardware no soportado para ILI9341-LTDC "
#endif
#define USE_DISPLAY
#define DISPLAY_DRV_ILI9341LTDC

#elif defined(BUILD_SSD1306)
#define HARDWARE_CUSTOM
#if defined(EOS_STM32F4)
#define HARDWARE_CUSTOM_STM32F429I_DISC1
#elif defined(EOS_STM32F7)
#define HARDWARE_CUSTOM_STM32F746G_DISCO
#elif defined(EOS_PIC32)
#define HARDWARE_CUSTOM_PIC32_USB_STARTER_KIT_I
#define DISPLAY_ADAFRUIT_SSD1306_128x64_D098
#else
#error "Hardware no soportado para ILI9341-LTDC "
#endif
#define DISPLAY_DRV_SSD1306

#else
#error "No se especifico el producto"
#endif

#define USE_LEDS_LED1
#define USE_LEDS_LED2
#define USE_SWITCHES_SW1


#include "board/eosBoard.h"


#endif // __eosConfig__
