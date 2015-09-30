#ifndef __EOS_H
#define	__EOS_H


#include <xc.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#ifndef __EOS_CONFIG_H
#include "eosConfig.h"
#endif


// Funcions d'inicialitzacio i configuracio
//
extern void eosInitialize(void);


// Funcions de gestio de memoria
//
#define eosAlloc(s)          eosHeapAlloc(NULL, s)
#define eosFree(p)           eosHeapFree(p)

#ifndef max
#define max(a, b)  (a) > (b) ? a : b
#define min(a, b)  (a) < (b) ? a : b
#endif

// Funcions de depuracio
//
#define eosDebugVerify(x)


#endif	

