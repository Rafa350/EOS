#ifndef __EOSMODULES_H
#define	__EOSMODULES_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Conversio AD
//
#ifdef eosUSE_ADC
extern UINT16 eosAdcGet(UINT8 adcId);

extern void sysAdcInitialize(void);
#endif

// Variables
//
#ifdef eosUSE_VARIABLES

typedef struct {
    UINT8 varId;
    unsigned value;
} VARINIT;

extern void eosVarSet(UINT8 id, unsigned value);
extern unsigned eosVarGet(UINT8 id);
extern void eosVarSave(void);
extern void eosVarRestore(void);
extern void eosVarSetTable(VARINIT *data, UINT8 dataLen);
#ifdef _PIC18
extern void eosVarSetTableROM(VARINIT *data, UINT8 dataLen);
#endif

extern void sysVarInitialize(void);

#endif


#endif	

