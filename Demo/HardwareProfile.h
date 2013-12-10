#ifndef __HARDWAREPROFILE_H
#define	__HARDWAREPROFILE_H


#ifdef HARDWARE_CPU04B

// Definicions pel oscilador
//
#define USE_OSC_XTAL

// Definicions pel modul d'entrades
//
#define EOS_NUM_INPUTS       10

// Definicio pl modul de sortides
//
#define EOS_NUM_OUTPUTS      10


#elif defined(HARDWARE_PICKIT3)

// Definicions per oscilador
//
#define USE_OSC_INTERNAL



#elif defined(HARDWARE_PIC32_ESK)

// Definicions per PLIB32
//
#define GetSystemClock()          (80000000L)
#define GetPeriphericalClock()    (GetSystemClock() / 2)


// Definicions pel modul d'entrades digitals
//
#define EOS_NUM_INPUTS       3    // Numero maxim d'entrades


// Definicions pel modul de sortides digitals
//
#define EOS_NUM_OUTPUTS      2    // Numero maxim de sortides


// Desinicions pel modul USB
//
#define EOS_USE_USBHOST

#endif

#endif

