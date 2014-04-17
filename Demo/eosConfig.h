#ifndef __EOSCONFIG_H
#define	__EOSCONFIG_H

#ifndef __HARDWAREPROFILE_H
#include "HardwareProfile.h"
#endif


// Opcions del sistema del sistema
//
#define eosOPT_SYSMAIN      // Utilitza la entrada del sistema
//#define eosOPT_WATCHDOG   // Utilitza el WatchDog
//#define eosOPT_FREERTOS   // Utilitza FreeRTOS
#define eosOPT_HARMONY      // Utilitza Harmony


// Configura el modul de depuracio (LED)
//
#define eosUSE_LED

// Configura el modul d'entrades (INPUTS)
//
//#define eosUSE_INPUTS
//#define eosCFG_INPUTS_NumInputs        8

// Configura el modul de sortides (OUTPUTS)
//
//#define eosUSE_OUTPUTS
//#define eosCFG_OUTPUTS_NumOutputs      7

// Configura el modul de temporitzadors (TIMERS)
//
#define eosUSE_TIMERS
#define eosCFG_TIMERS_NumTimers        16


// Configura el modul de variables (VARIABLES)
//
#define eosUSE_VARIABLES
#define eosCFG_VARIABLES_NumVariables  32


// Configura el modul i2c Master (I2CMASTER)
//


// Configura el modul i2cSlave (I2CSLAVE)
//


#endif

