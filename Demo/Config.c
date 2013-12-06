#include "eos.h"


#if (defined(HARDWARE_CPU03A) || defined(HARDWARE_CPU04B)) && \
    defined(_18F46K22)

// -----------------------------------------------------------------------
// MD-CPU03A (PIC18F46K22)
// -----------------------------------------------------------------------

// Opcions del oscilador
//
#if defined(USE_OSC_XTAL)
#pragma config IESO     = OFF //ON        // Oscilator switchover
#pragma config FCMEN    = OFF //ON        // Fail save clock monitor
#pragma config PRICLKEN = ON        // Primay clock activat sempre
#pragma config PLLCFG   = OFF       // PLL activat per OSTUNE.PLLEN
#pragma config FOSC     = HSMP      // Oscilator selection
#elif defined(USE_OSC_INTERNAL)
#pragma config IESO     = OFF //ON        // Oscilator switchover
#pragma config FCMEN    = OFF //ON        // Fail save clock monitor
#pragma config PRICLKEN = ON        // Primay clock activat sempre
#pragma config PLLCFG   = OFF       // PLL activat per OSTUNE.PLLEN
#pragma config FOSC     = INTIO67   // Oscilator selection intern
#else
#error "No se especifico el tipo de oscilador"
#endif

// Opcions de reset
//
#pragma config BORV     = 250       // Brown-out reset voltage
#pragma config BOREN    = OFF       // Brown-out reset
#pragma config STVREN   = ON        // Stack reset
#if defined(__DEBUG)
#pragma config PWRTEN   = OFF       // Power-up timer OFF
#else
#pragma config PWRTEN   = ON        // Power-up timer ON
#endif

// Opcions del watch-dog
//
#pragma config WDTPS    = 32768     // Watch-dog timer postscale
#if defined(EOS_USE_WATCHDOG) && !defined(__DEBUG)
#pragma config WDTEN    = SWON      // Watch-dog controlat per software
#else
#pragma config WDTEN    = OFF       // Watch-dog desactivat
#endif

#pragma config MCLRE    = EXTMCLR   // MCLR pin
#pragma config P2BMX    = 0
#pragma config T3CMX    = 0
#pragma config HFOFST   = 0
#pragma config CCP3MX   = 0
#pragma config PBADEN   = 0         // PORTB resetajat com entrada digital
#pragma config CCP2MX   = 0
#pragma config XINST    = OFF       // Extended instruction set

// Opcions de programacio
//
#if defined(__DEBUG)
#pragma config LVP      = OFF       // Single supply
#else
#pragma config LVP      = ON        // Single supply
#endif

// Opcions de proteccio de memoria
//
#pragma config CP3      = OFF       // Code protection
#pragma config CP2      = OFF       // Code protection
#pragma config CP3      = OFF       // Code protection
#pragma config CP0      = OFF       // Code protection
#pragma config CPD      = OFF       // Data EEPROM code protection
#pragma config CPB      = OFF       // Boot block code protection
#pragma config WRT3     = OFF       // Write protection
#pragma config WRT2     = OFF       // Write protection
#pragma config WRT1     = OFF       // Write protection
#pragma config WRT0     = OFF       // Write protection
#pragma config WRTD     = OFF       // Data EEPROM write protection
#pragma config WRTB     = OFF       // Boot block write protection
#pragma config WRTC     = OFF       // Configuration registar write protection
#pragma config EBTR3    = OFF       // Table read protection
#pragma config EBTR2    = OFF       // Table read protection
#pragma config EBTR1    = OFF       // Table read protection
#pragma config EBTR0    = OFF       // Table read protection
#pragma config EBTRB    = OFF       // Boot block table read protection


#elif defined(HARDWARE_PIC32_ESK) && \
      defined(__32MX795F512L__)

// -----------------------------------------------------------------------
// PIC32MX EHTERNET STARTER KIT (PIC32MX795F521L)
// -----------------------------------------------------------------------

// Configuracio del oscilador
//
#pragma config POSCMOD  = XT            // Primary Oscilator Configuration
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enabled
#pragma config FNOSC    = PRIPLL        // Oscilator Selection
#pragma config FPLLIDIV = DIV_2         // PLL Input divider
#pragma config FPLLODIV = DIV_1         // PLL Output divider
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config FPBDIV   = DIV_2         // Periferical clock divisor
#pragma config UPLLEN   = ON            // USB PLL Enabled
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider

// Configuracio del WatchDog
//
#pragma config FWDTEN   = OFF           // Watch-dog disabled
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale

// Configuracio per la proteccio de memoria de codi i dades
//
#pragma config CP       = OFF           // Proteccio de codi OFF

#else
    #error "No s'ha declarat el tipus de hardware"
#endif


