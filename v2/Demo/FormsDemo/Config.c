#include <xc.h>
#include "HardwareProfile.h"


// Configuracio del oscilador
//
#pragma config POSCMOD  = XT            // Primary Oscilator Configuration
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enabled
#pragma config FNOSC    = PRIPLL        // Oscilator Selection
#pragma config FPLLIDIV = DIV_2         // PLL Input divider
#pragma config FPLLODIV = DIV_1         // PLL Output divider
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config FPBDIV   = DIV_1         // Periferical clock divisor
#pragma config UPLLEN   = ON            // USB PLL Enabled
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider

// Configuracio del WatchDog
//
#pragma config FWDTEN   = OFF           // Watch-dog disabled
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale

// Configuracio per la proteccio de memoria de codi i dades
//
#ifdef __DEBUG
#pragma config CP       = OFF           // Proteccio de codi OFF
#else
#pragma config CP       = ON            // Proteccio de codi ON
#endif

// Configuracio del port de depuracio
//
#ifdef __DEBUG
#pragma config DEBUG    = ON            // Permet depuracio
#pragma config ICESEL   = ICS_PGx1      // Port de depuracio
#else
#pragma config DEBUG    = OFF           // Desactiva depuracio
#endif