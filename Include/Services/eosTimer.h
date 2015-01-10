#ifndef __EOS_TIMER_H
#define __EOS_TIMER_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
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

typedef void (*eosTimerCallback)(eosHTimer hTimer);

typedef struct {                       // Parametres de creacio d'un temporitzador
    unsigned timeout;                  // -Periode
    eosTimerType type;                 // -Tipus de temporitzador
    eosTimerCallback onTimeout;        // -Notifica timeout
} eosTimerParams;


// Gestio del servei
//
extern eosHTimerService eosTimerServiceInitialize(eosTimerServiceParams *params);
extern bool eosTimerServiceIsReady(eosHTimerService hService);
extern void eosTimerServiceTask(eosHTimerService hService);
extern void eosTimerServiceTick(eosHTimerService hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosHTimer eosTimerCreate(eosHTimerService hService, eosTimerParams *params);
extern void eosTimerDestroy(eosHTimer hTimer);

// Operacions amb els objectes
//
extern void eosTimerPause(eosHTimer hTimer);
extern void eosTimerContinue(eosHTimer hTimer);
extern void eosTimerReset(eosHTimer hTimer);

// Operacions especials
//
extern eosHTimer eosTimerDelayStart(eosHTimerService hService, unsigned timeout);
extern bool eosTimerDelayGetStatus(eosHTimer timer);


#endif

