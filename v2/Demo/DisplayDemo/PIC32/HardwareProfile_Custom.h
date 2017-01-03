#ifndef __HARDWARE_PROFILE_CUSTOM_H
#define __HARDWARE_PROFILE_CUSTOM_H


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)

// -----------------------------------------------------------------------
// LEDS
// -----------------------------------------------------------------------

#define LEDS_LD1_PORT        HAL_GPIO_PORT_G
#define LEDS_LD1_PIN         HAL_GPIO_PIN_6

#define LEDS_LD2_PORT        HAL_GPIO_PORT_D
#define LEDS_LD2_PIN         HAL_GPIO_PIN_1


// -----------------------------------------------------------------------
// TFT ILI9341
// -----------------------------------------------------------------------


//   ILI9341             PINGUINO      GPIO     
//   -------             --------      ----  
//        10     RST     CON1-13       RD11
//        35     RD      CON1-1        RC14     
//        36     WR      CON1-15       RD7      
//        37     RS      CON1-2        RC13     
//        38     CS      CON1-14       RD8      
//               DATA    CON1-3..10    RE0..7   

// Tipus de pantalla
//
#define DISPLAY_ER_TFT028_4
//#define DISPLAY_COLOR_ARGB
//#define DISPLAY_COLOR_RGB
#define DISPLAY_COLOR_565
//#define DISPLAY_COLOR_PALETTE

// Tipus de lletra disponibles 
//
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt


#define ILI9341_COLORMODE_565
//#define ILI9341_COLORMODE_666

//#define ILI9341_INTERFACE_MODE_HAL_GPIO
#define ILI9341_INTERFACE_MODE_PIC32_GPIO
//#define ILI9341_INTERFACE_MODE_PIC32_PMP
//#define ILI9341_INTERFACE_MODE_STM32_GPIO

#define ILI9341_INTERFACE_TYPE_PARALEL_8BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_9BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_16BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_18BIT
//#define ILI9341_INTERFACE_TYPE_PIC32PMP_8BIT


// Control del pin RST (Reset) CON1-13
//
#define ILI9341_RST_PORT     HAL_GPIO_PORT_D
#define ILI9341_RST_PIN      HAL_GPIO_PIN_11

// Control del pin CS (Chip select) CON1-14
//
#define ILI9341_CS_PORT      HAL_GPIO_PORT_D
#define ILI9341_CS_PIN       HAL_GPIO_PIN_8

// Control del pin RS (Register select) CON1-2
//
#define ILI9341_RS_PORT      HAL_GPIO_PORT_C
#define ILI9341_RS_PIN       HAL_GPIO_PIN_13

// Control de pin WR (Write) D7 CON1-15
//
#define ILI9341_WR_PORT      HAL_GPIO_PORT_D
#define ILI9341_WR_PIN       HAL_GPIO_PIN_7

// Control del pin RD (Read) CON1-1
//
#define ILI9341_RD_PORT      HAL_GPIO_PORT_C
#define ILI9341_RD_PIN       HAL_GPIO_PIN_14

// Control del port DATA (I/O paralel port) CON1-3..10
//
#define ILI9341_DATA_PORT    HAL_GPIO_PORT_E


#endif