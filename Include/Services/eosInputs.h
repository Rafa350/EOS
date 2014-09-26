#ifndef __EOS_INPUTS_H
#define	__EOS_INPUTS_H

#ifndef __EOS_H
#include "eos.h"
#endif

#include "peripheral/ports/plib_ports.h"


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
    eosInputEvent callOn;         // -Event on es crida a la funcio
    eosCallback callback;         // -Funcio callback
    void *context;                // -Parametre de la funcio callback
} eosInputCreateParams;

typedef struct {                  // Parametres d'inicialitzacio del servei
    unsigned maxInputs;           // -Numero maxim d'entrades a procesar
    unsigned maxEventQueue;       // -Numero maxim d'events en la cua
    eosHandle hTickService;       // -Servei TICK
} eosInputsInitializeParams;


extern eosResult eosInputsInitialize(eosInputsInitializeParams *params, eosHandle *hService);
extern eosResult eosInputsTerminate(eosHandle hService);
extern eosResult eosInputsTask(eosHandle hService);

extern void eosInputsISRTick(void *context);

extern eosResult eosInputsCreate(eosHandle hService, eosInputCreateParams *params, eosHandle *hInput);
extern eosResult eosInputsDestroy(eosHandle hInput);

extern BOOL eosInputGet(eosHandle hInput);
extern BOOL eosInputPosEdge(eosHandle hInput);
extern BOOL eosInputNegEdga(eosHandle hInput);


#endif	

