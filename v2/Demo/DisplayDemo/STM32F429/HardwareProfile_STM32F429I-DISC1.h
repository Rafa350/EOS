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
//
//   Interface P8
//
//   ILI9341             PINGUINO
//   -------             --------
//        10     RST     CON1-13
//        35     RD      CON1-1
//        36     WR      CON1-15
//        37     RS      CON1-2
//        38     CS      CON1-14
//
//   Interface 4WIRE2
//


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

#define ILI9341_INTERFACE_TYPE_PARALEL_8BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_9BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_16BIT
//#define ILI9341_INTERFACE_TYPE_PARALEL_18BIT


// Control del pin RST (Reset) CON1-13
//
#define ILI9341_RSTPort      D
#define ILI9341_RSTPin      11

// Control del pin CS (Chip select) CON1-14
//
#define ILI9341_CSPort       D
#define ILI9341_CSPin        8

// Control del pin RS (Register select) CON1-2
//
#define ILI9341_RSPort       C
#define ILI9341_RSPin        13

// Control del pin CLK (Serial clock) CON1-2
//
//#define ILI9341_CLKPort      C
//#define ILI9341_CLKPin       13

// Control del pin SO (Serial data output) CON1-3
//
//#define ILI9341_SOPort       C
//#define ILI9341_SOPin        14

// Control del pin SI (Serial data input)
//
//#define ILI9341_SIPort       G
//#define ILI9341_SIPin        9

// Control de pin WR (Write) D7 CON1-15
//
#define ILI9341_WRPort       D
#define ILI9341_WRPin        7

// Control del pin RD (Read) CON1-1
//
#define ILI9341_RDPort       C
#define ILI9341_RDPin        14

// Control del port DATA (I/O paralel port) CON1-3..10
//
#define ILI9341_DATAPort     E


#endif
