#ifndef __EOSCONFIG_H
#define	__EOSCONFIG_H

#ifndef __HARDWAREPROFILE_H
#include "hardwareprofile.h"
#endif


// Parametres del sistema
//
#define EOS_USE_SYSMAIN
#define EOS_USE_LEDSTATUS
//#define EOS_USE_WATCHDOG
//#define EOS_USE_FREERTOS


// Parametres del modul d'entrades digitals
//
#define EOS_USE_INPUTS            // Activa el modul
#ifndef EOS_NUM_INPUTS
#define EOS_NUM_INPUTS    16      // Numero maxim d'entrades
#endif


// Parametres del modul de sortides digitals
//
#define EOS_USE_OUTPUTS           // Activa el modul
#ifndef EOS_NUM_OUTPUTS
#define EOS_NUM_OUTPUTS   16      // Numero maxim de sortides
#endif


// Parametres del modul de temporitzadors
//
#define EOS_USE_TIMERS            // Activa el modul
#define EOS_NUM_TIMERS    16      // Numero maxim de temporitzadors


// Parametres del modul de variables
//
#define EOS_USE_VARIABLES         // Activa el modul
#define EOS_NUM_VARIABLES 64      // Numero maxim de variables


// Parametres del modul USB
//
//#define EOS_USE_USBHOST           // Activa el modul


#endif

