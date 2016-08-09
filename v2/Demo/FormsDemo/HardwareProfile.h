#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H


// Configuracio del sistema
//
#define CLOCK_SYSTEM_HZ            80000000
#define CLOCK_PERIPHERICAL_HZ      (CLOCK_SYSTEM_HZ / 1)


// -----------------------------------------------------------------------
// CONFIGURACIO DEL DRIVER DEL DISPLAY ILI9341
// -----------------------------------------------------------------------


// Tipus de lletra  disponibles 
//
#define FONT_USE_Consolas8pt
#define FONT_USE_Consolas10pt
#define FONT_USE_Consolas12pt
#define FONT_USE_Consolas14pt
#define FONT_USE_Consolas18pt
#define FONT_USE_Consolas24pt


// Format de color dels pixels
//
#define ILI9341_COLORMODE_565
//#define ILI9341_COLORMODE_666

// Tipus d'interficie amb el controlador
//
#define ILI9341_READONLY
#define ILI9341_INTERFACE_4WIRE2
//#define ILI9341_INTERFACE_P8
//#define ILI9341_INTERFACE_P9
//#define ILI9341_INTERFACE_P16
//#define ILI9341_INTERFACE_P18

// Control del pin RST (Reset) RD11
//
#define ILI9341_RSTPort      D
#define ILI9341_RSTPin      11

// Control del pin CS (Chip select) RD8
//
#define ILI9341_CSPort       D
#define ILI9341_CSPin        8

// Control del pin RS (Register select) RD7
//
#define ILI9341_RSPort       D
#define ILI9341_RSPin        7

// Control del pin CLK (Serial clock) RC13
//
#define ILI9341_CLKPort      C
#define ILI9341_CLKPin       13

// Control del pin SO (Serial data output) RC14
//
#define ILI9341_SOPort       C
#define ILI9341_SOPin        14

// Control del pin SI (Serial data input) RE3
//
#define ILI9341_SIPort       G
#define ILI9341_SIPin        9

// Control de pin WR (Write)
//
#define ILI9341_WRPort
#define ILI9341_WRPin

// Control del pin RD (Read)
//
#define ILI9341_RDPort
#define ILI9341_RDPin

// Control del port DATA (I/O paralel port)
//
#define ILI9341_DATAPort


#endif