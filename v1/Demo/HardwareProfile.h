#ifndef __HARDWAREPROFILE_H
#define	__HARDWAREPROFILE_H


#ifdef HARDWARE_CPU04B

// Definicions pel oscilador
//
#define USE_OSC_XTAL

// Configura el modul d'entrades
//
#define eosUSE_INPUTS
#define eosCFG_INPUTS_NumInputs        10

// Configura el modul de sortides
//
#define eosUSE_OUTPUTS
#define eosCFG_OUTPUTS_NumOutputs      10


#elif defined(HARDWARE_PICKIT3)

#define USE_OSC_INTERNAL

// Definicions pel modul d'entrades
//
#define eosUSE_INPUTS                       // Utilitza el modul d'entrades
#define eosCFG_INPUTS_NumInputs        2    // Numero maxim d'entrades

// Definicios pel modul de sortides
//
#define eosUSE_OUTPUTS                      // Utilitza el modul de sortides
#define eosCFG_OUTPUTS_NumOutputs      6    // Numero maxim de sortides

// Definicions pel modul de control de motors
//
#define eosUSE_STEP                         // Utilitza el modul de control de motor
#define eosCFG_STEP_NumMotors          3    // Numero de motors


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
