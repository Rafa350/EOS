#ifndef __EOS_TIMERS_H
#define __EOS_TIMERS_H

#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
#endif


#ifndef __EOS_TIMERS_INTERNAL
struct __eosTimer {};
struct __eosTimerService {};
#endif

typedef struct __eosTimer *eosHTimer;
typedef struct __eosTimerService *eosHTimerService;

typedef struct {                       // Parametres d'inicialitzacio del servei
    eosHTickService hTickService;      // -Servei TICK
} eosTimerServiceParams;

typedef enum {                         // Tipus de temporitzador
    TT_ONE_SHOT,                       // -Un sol tret
    TT_ONE_SHOT_AUTODESTROY,           // -Un sol tret amb autodestruccio
    TT_CYCLIC,                         // -Ciclic
} eosTimerType;

typedef struct {                       // Parametres de creacio d'un temporitzador
    unsigned timeout;                  // -Periode
    eosTimerType type;                 // -Tipus de temporitzador
    eosCallback onTimeout;             // -Evemnt TIMEOUT
    void *context;                     // -Parametre dels events
} eosTimerParams;


// Gestio del servei
//
extern eosResult eosTimerServiceInitialize(eosTimerServiceParams* params, eosHTimerService *hService);
extern void eosTimerServiceTask(eosHTimerService hService);
extern void eosTimerServiceISRTick(eosHTimerService hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosResult eosTimerCreate(eosHTimerService hService, eosTimerParams* params, eosHTimer *hTimer);
extern eosResult eosTimerDestroy(eosHTimer hTimer);

// Operacions amb els objectes
//
extern eosResult eosTimerPause(eosHTimer hTimer);
extern eosResult eosTimerContinue(eosHTimer hTimer);
extern eosResult eosTimerReset(eosHTimer hTimer);

// Operacions especials
//
extern eosHTimer eosTimerDelayStart(eosHTimerService hService, unsigned timeout);
extern BOOL eosTimerDelayGetStatus(eosHTimer timer);


#endif

