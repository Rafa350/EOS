#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H


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
// CONFIGURACIO DE LA PANTALLA ILI9341
// -----------------------------------------------------------------------

#define ILI9341_COLORMODE_RGB16bit
#define ILI9341_INTERFACE_4WIRE2

// Control del pin CS (Chip select) RE1
//
#define ILI9341_initCS()  LATESET  = 1 << 1; \
                          TRISECLR = 1 << 1
#define ILI9341_setCS()   LATESET  = 1 << 1
#define ILI9341_clrCS()   LATECLR  = 1 << 1

// Control del pin RS (Register select) RE2
//
#define ILI9341_initRS()  LATECLR  = 1 << 2; \
                          TRISECLR = 1 << 2
#define ILI9341_setRS()   LATESET  = 1 << 2
#define ILI9341_clrRS()   LATECLR  = 1 << 2

// Control del pin CLK (Serial clock) RE5
//
#define ILI9341_initCLK() LATESET  = 1 << 5; \
                          TRISECLR = 1 << 5
#define ILI9341_setCLK()  LATESET  = 1 << 5
#define ILI9341_clrCLK()  LATECLR  = 1 << 5

// Control del pin SO (Serial output) RE4
//
#define ILI9341_initSO()  TRISECLR = 1 << 4
#define ILI9341_setSO()   LATESET  = 1 << 4
#define ILI9341_clrSO()   LATECLR  = 1 << 4

// Control del pin SI (Serial inpout) RE3
//
#define ILI9341_initSI()  TRISESET = 1 << 3
#define ILI9341_getSI()   (PORTE & ~(1 << 3) != 0)

// Control del pin RST (Reset) RE0
//
#define ILI9341_initRST() LATECLR  = 1 << 0; \
                          TRISECLR = 1 << 0
#define ILI9341_setRST()  LATESET  = 1 << 0
#define ILI9341_clrRST()  LATECLR  = 1 << 0


#endif