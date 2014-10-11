#ifndef __EOS_INPUTS_H
#define	__EOS_INPUTS_H

#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif

#ifndef __EOS_INPUTS_H__
struct __INPUT {};
typedef struct __INPUT eosInput;

struct __INPUT_SERVICE {};
typedef struct __INPUT_SERVICE eosInputService;
#endif


// Quant hi ha que fer la crida
//
#define INPUT_ON_CHANGE      0    // Quant hi ha un canvi
#define INPUT_ON_POSEDGE     1    // Qunat hi ha un flanc positiu
#define INPUT_ON_NEGEDGE     2    // Qunat hi ha un flanc negatiu

typedef struct {                  // Context de la funcio callback
    eosInputService* service;     // -El servei
    eosInput* input;              // -L'entrada
    void *context;                // -Contexte definit en l'aplicacio d'usuari
    unsigned when;                // -Quant hi ha que fer la crida
} eosInputCallbackContext;

typedef struct {                  // Parametres de creacio d'entrades
    PORTS_CHANNEL channel;        // -Canal del port
    PORTS_BIT_POS position;       // -Pin del port
    BOOL inverted;                // -Inverteix la entrada
    unsigned when;                // -Quant hi ha que fer la crida
    eosCallback callback;         // -Funcio callback
    void *context;                // -Parametre de la funcio callback
} eosInputParams;

typedef struct {                  // Parametres d'inicialitzacio del servei
    unsigned maxEventQueue;       // -Numero maxim d'events en la cua
    eosHandle hTickService;       // -Servei TICK
} eosInputServiceParams;


// Gestio del servei
//
extern eosInputService* eosInputServiceInitialize(eosInputServiceParams* params);
extern void eosInputServiceTask(eosInputService* Service);
extern void eosInputServiceISRTick(void* context);

// Creacio, destruccio i gestio dels objectes
//
extern eosInput* eosInputCreate(eosInputService* service, eosInputParams* params);
extern void eosInputDestroy(eosInput* input);

// Operacions amb els objectes
//
extern BOOL eosInputsGet(eosInput* input);
extern BOOL eosInputsPosEdge(eosInput* input);
extern BOOL eosInputsNegEdga(eosInput* input);


#endif	

