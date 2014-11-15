#ifndef __EOS_INPUTS_H
#define	__EOS_INPUTS_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_TICK_H
#include "Services/eosTick.h"
#endif

#ifndef _PLIB_PORTS_H
#include "peripheral/ports/plib_ports.h"
#endif


// Quant hi ha que fer la crida
//
#define INPUT_ON_CHANGE           0    // Quant hi ha un canvi
#define INPUT_ON_POSEDGE          1    // Qunat hi ha un flanc positiu
#define INPUT_ON_NEGEDGE          2    // Qunat hi ha un flanc negatiu


#ifndef __EOS_INPUTS_INTERNAL
struct __axInput {};
struct __axInputService {};
#endif

typedef struct __eosInput *eosHInput;
typedef struct __eosInputService *eosHInputService;

typedef struct {                       // Context de la funcio callback
    eosHInputService hService;         // -El handler del servei
    eosHInput hInput;                  // -El handler de l'entrada
    void *context;                     // -Contexte definit en l'aplicacio d'usuari
    unsigned when;                     // -Quant hi ha que fer la crida
} eosInputCallbackContext;

typedef struct {                       // Parametres d'inicializacio de les entrades
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    BOOL inverted;                     // -Inverteix la entrada
    unsigned when;                     // -Quant hi ha que fer la crida
    eosCallback callback;              // -Funcio callback
    void *context;                     // -Parametre de la funcio callback
} eosInputParams;

typedef struct {                       // Parametres d'inicialitzacio del servei
    eosHTickService hTickService;      // -Servei TICK
} eosInputServiceParams;


// Gestio del servei
//
extern eosResult eosInputServiceInitialize(eosInputServiceParams *params, eosHInputService *hService);
extern void eosInputServiceTask(eosHInputService hService);
extern void eosInputServiceISRTick(eosHInputService hService);

// Creacio, destruccio i gestio dels objectes
//
extern eosResult eosInputCreate(eosHInputService hService, eosInputParams *params, eosHInput *hInput);
extern eosResult eosInputDestroy(eosHInput hInput);

// Operacions amb els objectes
//
extern BOOL eosInputGet(eosHInput hInput);
extern BOOL eosInputPosEdge(eosHInput hInput);
extern BOOL eosInputNegEdge(eosHInput hInput);


#endif	

