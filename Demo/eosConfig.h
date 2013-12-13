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
#define EOS_USE_HARMONY


// Definicions pel modul de temporitzadors
//
#define eosPLC_UseTimers
#define eosPLC_NumTimers     16

// Definicions pel modul de variables
//
#define eosPLC_UseVariables
#define eosPLC_NumVariables  32

#endif

