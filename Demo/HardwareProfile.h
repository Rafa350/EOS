#ifndef __HARDWAREPROFILE_H
#define	__HARDWAREPROFILE_H


#ifdef HARDWARE_CPU04B

// Definicions pel oscilador
//
#define USE_OSC_XTAL

// Definicions pel modul d'entrades
//
#define eosCFG_INPUTS_NumInputs        10

// Definicio pl modul de sortides
//
#define eosCFG_OUTPUTS_NumOutputs      10


#elif defined(HARDWARE_PICKIT3)

// Definicions per oscilador
//
#define USE_OSC_INTERNAL

// Definicions pel modul d'entrades
//
#define eosPLC_UseInputs          // Utilitza el modul d'entrades
#define eosPLC_NumInputs     2    // Numero maxim d'entrades

// Definicios pel modul de sortides
//
#define eosPLC_UseOutputs         // Utilitza el modul de sortides
#define eosPLC_NumOutputs    7    // Numero maxim de sortides


#elif defined(HARDWARE_PIC32_ESK)

// Definicions per PLIB32
//
#define GetSystemClock()          (80000000L)
#define GetPeriphericalClock()    (GetSystemClock() / 1)


// Definicions pel modul d'entrades digitals
//
#define eosPLC_UseInputs
#define eosPLC_NumInputs     3    // Numero maxim d'entrades


// Definicions pel modul de sortides digitals
//
#define eosPLC_UseOutputs
#define eosPLC_NumOutputs    2    // Numero maxim de sortides


// Desinicions pel modul USB
//
//#define EOS_USE_USBHOST

#endif

#endif

