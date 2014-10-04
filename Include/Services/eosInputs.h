#ifndef __EOS_INPUTS_H
#define	__EOS_INPUTS_H

#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif


typedef enum {                    // Events del servei
    inputEventChange,             // -Quant hi ha canvi
    inputEventPosEdge,            // -Quant es un flanc positiu
    inputEventNegEdge             // -Quant es un flanc negatiu
} eosInputEvent;

typedef struct {                  // Context de la funcio callback
    eosHandle hService;           // -Handler del servei
    eosHandle hInput;             // -Handler de la entrada
    void *context;                // -Contexte definit en l'aplicacio d'usuari
    eosInputEvent event;          // -Event que ha generat la crida
} eosInputCallbackContext;

typedef struct {                  // Paramstres de creacio d'entrades
    PORTS_CHANNEL channel;        // -Canal del port
    PORTS_BIT_POS position;       // -Pin del port
    BOOL inverted;                // -Inverteix la entrada
    eosInputEvent callEvent;      // -Event on es crida a la funcio
    eosCallback callback;         // -Funcio callback
    void *context;                // -Parametre de la funcio callback
} eosInputsCreateParams;

typedef struct {                  // Parametres d'inicialitzacio del servei
    unsigned maxInputs;           // -Numero maxim d'entrades a procesar
    unsigned maxEventQueue;       // -Numero maxim d'events en la cua
    eosHandle hTickService;       // -Servei TICK
} eosInputsInitializeParams;


// Inicialitzacio, finalitzacio i gestio del servei
//
extern eosResult eosInputsInitialize(eosInputsInitializeParams *params, eosHandle *hService);
extern eosResult eosInputsTerminate(eosHandle hService);
extern eosResult eosInputsTask(eosHandle hService);
extern void eosInputsISRTick(void *context);

// Creacio, destruccio i gestio dels objectes
//
extern eosResult eosInputsCreate(eosHandle hService, eosInputsCreateParams *params, eosHandle *hInput);
extern eosResult eosInputsDestroy(eosHandle hInput);

// Operacions amb els objectes
//
extern BOOL eosInputsGet(eosHandle hInput);
extern BOOL eosInputsPosEdge(eosHandle hInput);
extern BOOL eosInputsNegEdga(eosHandle hInput);


#endif	

