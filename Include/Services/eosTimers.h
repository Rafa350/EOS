#ifndef __EOS_TIMERS_H
#define __EOS_TIMERS_H

#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TIMERS_H__
struct __TIMER {};
typedef struct __TIMER eosTimer;

struct __TIMER_SERVICE {};
typedef struct __TIMER_SERVICE eosTimerService;
#endif


typedef struct {                       // Parametres d'inicialitzacio del servei
    eosHandle hTickService;            // -Servei TICK
} eosTimerServiceParams;

typedef enum {                         // Tipus de temporitzador
    TT_ONE_SHOT,                       // -Un sol tret
    TT_ONE_SHOT_AUTODESTROY,           // -Un sol tret amb autodestruccio
    TT_CYCLIC,                         // -Ciclic
} eosTimerType;

typedef struct {                       // Parametres de creacio d'un temporitzador
    unsigned timeout;                  // -Periode
    eosTimerType type;                 // -Tipus de temporitzador
    eosCallback callback;              // -Funcio callback
    void *context;                     // -Parametre de la funcio callback
} eosTimerParams;


// Gestio del servei
//
extern eosTimerService* eosTimerServiceInitialize(eosTimerServiceParams* params);
extern void eosTimerServiceTask(eosTimerService* service);
extern void eosTimerServiceISRTick(void* context);

// Creacio, destruccio i gestio dels objectes
//
extern eosTimer* eosTimerCreate(eosTimerService* service, eosTimerParams* params);
extern void eosTimerDestroy(eosTimer* timer);

// Operacions amb els objectes
//
extern void eosTimerPause(eosTimer* timer);
extern void eosTimerContinue(eosTimer* timer);
extern void eosTimerReset(eosTimer* timer);

// Operacions especials
//
extern eosTimer* eosTimerDelayStart(eosTimerService* service, unsigned timeout);
extern BOOL eosTimerDelayGetStatus(eosTimer* timer);


#endif

