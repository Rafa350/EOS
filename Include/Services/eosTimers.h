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

typedef struct __eosTimer *eosTimer;
typedef struct __eosTimerService *eosTimerService;

typedef struct {                       // Parametres d'inicialitzacio del servei
    eosTickService tickService;        // -Servei TICK
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
extern eosResult eosTimerServiceInitialize(eosTimerServiceParams* params, eosTimerService *service);
extern void eosTimerServiceTask(eosTimerService service);
extern void eosTimerServiceISRTick(eosTimerService service);

// Creacio, destruccio i gestio dels objectes
//
extern eosResult eosTimerCreate(eosTimerService service, eosTimerParams* params, eosTimer *timer);
extern eosResult eosTimerDestroy(eosTimer timer);

// Operacions amb els objectes
//
extern void eosTimerPause(eosTimer timer);
extern void eosTimerContinue(eosTimer timer);
extern void eosTimerReset(eosTimer timer);

// Operacions especials
//
extern eosTimer eosTimerDelayStart(eosTimerService service, unsigned timeout);
extern BOOL eosTimerDelayGetStatus(eosTimer timer);


#endif

