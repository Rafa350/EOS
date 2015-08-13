#ifndef __EOS_TIMER_H
#define __EOS_TIMER_H


#include "eos.h"


typedef struct __eosTimerService *eosTimerServiceHandle;
typedef struct __eosTimer *eosTimerHandle;

typedef struct {                       // Parametres d'inicialitzacio del servei
    unsigned maxTimers;                // -Numero maxim de timers
} eosTimerServiceParams;

typedef enum {                         // Tipus de temporitzador
    TT_ONE_SHOT,                       // -Un sol tret
    TT_ONE_SHOT_AUTODESTROY,           // -Un sol tret amb autodestruccio
    TT_CYCLIC,                         // -Ciclic
} eosTimerType;

typedef void (*eosTimerCallback)(eosTimerHandle hTimer);

typedef struct {                       // Parametres de creacio d'un temporitzador
    unsigned timeout;                  // -Periode
    eosTimerType type;                 // -Tipus de temporitzador
    eosTimerCallback onTimeout;        // -Notifica timeout
} eosTimerParams;


// Gestio del servei
//
extern eosTimerServiceHandle eosTimerServiceInitialize(eosTimerServiceParams *params);
extern bool eosTimerServiceIsReady(eosTimerServiceHandle hService);
extern void eosTimerServiceTask(eosTimerServiceHandle hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosTimerHandle eosTimerCreate(eosTimerServiceHandle hService, eosTimerParams *params);
extern void eosTimerDestroy(eosTimerHandle hTimer);

// Operacions amb els objectes
//
extern void eosTimerPause(eosTimerHandle hTimer);
extern void eosTimerContinue(eosTimerHandle hTimer);
extern void eosTimerReset(eosTimerHandle hTimer);

// Operacions especials
//
extern eosTimerHandle eosTimerDelayStart(eosTimerServiceHandle hService, unsigned timeout);
extern bool eosTimerDelayGetStatus(eosTimerHandle hTimer);


#endif

