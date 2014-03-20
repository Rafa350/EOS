#ifndef __EOSPLC_H
#define	__EOSPLC_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Sortides digitals
//
#ifdef eosUSE_OUTPUTS

extern void eosOutSet(UINT8 id, BOOL state);
extern void eosOutToggle(UINT8 id);
extern void eosOutPulse(UINT8 id, unsigned timeOut);
extern void eosOutBlink(UINT8 id, unsigned timeOut);
extern void eosOutAllOFF(void);

#define eosOutSetON(id)                eosOutSet(id, TRUE)
#define eosOutSetOFF(id)               eosOutSet(id, FALSE)

extern void sysOutInitialize(void);
extern void sysOutLoop(void);
extern void sysOutTickInterrupt(void);

#endif

// Entrades digitals
//
#ifdef eosUSE_INPUTS

extern BOOL eosInpGet(UINT8 id);
extern BOOL eosInpPosEdge(UINT8 id);
extern BOOL eosInpNegEdge(UINT8 id);

extern void sysInpInitialize(void);
extern void sysInpLoop(void);
extern void sysInpTickInterrupt(void);

#endif

// Conversio AD
//
#ifdef eosUSE_ADC
extern UINT16 eosAdcGet(UINT8 adcId);

extern void sysAdcInitialize(void);
#endif

// Temporitzadors
//
#ifdef eosUSE_TIMERS
extern void eosTimStart(UINT8 id, unsigned time);
extern BOOL eosTimGet(UINT8 id);
extern void eosTimPause(UINT8 id);
extern void eosTimContinue(UINT8 id);

extern void sysTimInitialize(void);
extern void sysTimLoop(void);
extern void sysTimTickInterrupt(void);
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

