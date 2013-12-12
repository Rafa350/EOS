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
#define EOS_USE_TIMERS
#define EOS_NUM_TIMERS       16

// Definicions pel modul de variables
//
#define EOS_USE_VARIABLES
#define EOS_NUM_VARIABLES    32

#endif

