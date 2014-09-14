#ifndef __EOS_TIMERS_H
#define __EOS_TIMERS_H

#ifndef __EOS_H
#include "eos.h"
#endif


// Codis d'error
//
#define eos_ERROR_TIMER_UNAVAILABLE    eos_ERROR_FIRST


typedef void (*eosTimerCallback)(void *context);


typedef struct {                       // Parametres d'inicialitzacio del servei
    unsigned maxTimers;                // -Numero maxim de temporitzadors
    eosHandle hTickService;            // -Servei TICK
} eosTimerInitializeParams;

typedef enum {                         // Tipus de temporitzador
    TT_ONE_SHOT,                       // -Un sol tret
    TT_ONE_SHOT_AUTODESTROY,           // -Un sol tret amb autodestruccio
    TT_CYCLIC,                         // -Ciclic
} eosTimerType;

typedef struct {                       // Parametres de creacio d'un temporitzador
    unsigned timeout;                  // -Periode
    eosTimerType type;                 // -Tipus de temporitzador
    eosTimerCallback callback;         // -Funcio callback
    void *context;                     // -Parametre de la funcio callback
} eosTimerCreateParams;


extern eosResult eosTimerInitialize(eosTimerInitializeParams *params, eosHandle *hService);
extern eosResult eosTimerTerminate(eosHandle hService);
extern eosResult eosTimerTask(eosHandle hService);

extern void eosTimerISRTick(void *context);

extern eosResult eosTimerCreate(eosHandle hService, eosTimerCreateParams *params, eosHandle *hTimer);
extern eosResult eosTimerDestroy(eosHandle hTimer);
extern eosResult eosTimerPause(eosHandle hTimer);
extern eosResult eosTimerContinue(eosHandle hTimer);
extern eosResult eosTimerReset(eosHandle hTimer);

extern eosHandle eosTimerDelayStart(eosHandle hService, unsigned timeout);
extern BOOL eosTimerDelayGetStatus(eosHandle hTimer);


#endif

