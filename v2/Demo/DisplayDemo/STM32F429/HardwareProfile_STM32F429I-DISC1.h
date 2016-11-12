#ifndef __HARDWARE_PROFILE_SMT32F429_DISC1_H
#define __HARDWARE_PROFILE_SMT32F429_DISC1_H


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// LEDS
// -----------------------------------------------------------------------

#define LEDS_LD1_PORT        GPIO_PORT_G
#define LEDS_LD1_PIN         GPIO_PIN_13

#define LEDS_LD2_PORT        GPIO_PORT_G
#define LEDS_LD2_PIN         GPIO_PIN_14


// -----------------------------------------------------------------------
// TFT ILI9341
// -----------------------------------------------------------------------

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

#define ILI9341_INTERFACE_MODE_HAL_GPIO
//#define ILI9341_INTERFACE_MODE_PIC32_GPIO
//#define ILI9341_INTERFACE_MODE_PIC32_PMP
//#define ILI9341_INTERFACE_MODE_STM32_GPIO

//#define ILI9341_INTERFACE_TYPE_PARALEL_8BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_9BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_16BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_18BIT
#define ILI9341_INTERFACE_TYPE_SERIAL_8BIT

#define ILI9341_INTERFACE_WRITEONLY


// Control del pin CS (Chip select)
//
#define ILI9341_CS_PORT      GPIO_PORT_C
#define ILI9341_CS_PIN       GPIO_PIN_2

// Control del pin RS (Register select)
//
#define ILI9341_RS_PORT      GPIO_PORT_D
#define ILI9341_RS_PIN       GPIO_PIN_13

// Control del pin CLK (Serial clock)
//
#define ILI9341_CLK_PORT     GPIO_PORT_F
#define ILI9341_CLK_PIN      GPIO_PIN_7

// Control del pin SO (Serial data output to controller MOSI)
//
#define ILI9341_SO_PORT      GPIO_PORT_F
#define ILI9341_SO_PIN       GPIO_PIN_9



#endif
