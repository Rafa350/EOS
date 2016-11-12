#ifndef __HARDWARE_PROFILE_SMT32F429_DISC1_H
#define __HARDWARE_PROFILE_SMT32F429_DISC1_H


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// CONFIGURACIO DE LA PLACA PIC32MX-ESK
// -----------------------------------------------------------------------

// Configuracio dels leds indicadors
//
#define pinLED1         0
#define pinLED2         1
#define pinLED3         2

// Configuracio del switches
//
#define pinSW1          3
#define pinSW2          4
#define pinSW3          5


// -----------------------------------------------------------------------
// CONFIGURACIO DEL DRIVER DEL DISPLAY ILI9341
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
#define ILI9341_CSPort       C
#define ILI9341_CSPin        2

// Control del pin RS (Register select)
//
#define ILI9341_RSPort       D
#define ILI9341_RSPin        13

// Control del pin CLK (Serial clock)
//
#define ILI9341_CLKPort      F
#define ILI9341_CLKPin       7

// Control del pin SO (Serial data output to controller MOSI)
//
#define ILI9341_SOPort       F
#define ILI9341_SOPin        9



#endif
