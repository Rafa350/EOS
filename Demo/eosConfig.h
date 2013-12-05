#ifndef __EOSCONFIG_H
#define	__EOSCONFIG_H

#ifndef __HARDWAREPROFILE_H
#include "hardwareprofile.h"
#endif


// Parametres del systema
//
#define EOS_USE_SYSMAIN
//#define EOS_USE_WATCHDOG


// Parametres del modul d'entrades digitals
//
//#define EOS_USE_INPUTS            // Activa el modul
#define EOS_NUM_INPUTS    16      // Numero maxim d'entrades


// Parametres del modul de sortides digitals
//
#define EOS_USE_OUTPUTS           // Activa el modul
#define EOS_NUM_OUTPUTS   16      // Numero m'axim de sortides


#endif

