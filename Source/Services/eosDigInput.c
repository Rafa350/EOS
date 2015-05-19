#include "Services/eosDigInput.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -En execucio
} eosDigInputServiceState;

#define PATTERN_ON       0x00007FFF
#define PATTERN_OFF      0x00008000
#define PATTERN_MASK     0x0000FFFF


typedef struct __eosDigInput {         // Dades d'una entrada
    eosDigInputServiceHandle hService; // -El servei al que pertany
    eosDigInputHandle hNextInput;      // -Seguent element
    unsigned port;                     // -Canal del port
    unsigned pin;                      // -Pin del port
    bool inverted;                     // -Senyal invertida
    eosDigInputCallback onPosEdge;     // -Event POSEDGE
    eosDigInputCallback onNegEdge;     // -Event NEGEDGE
    eosDigInputCallback onChange;      // -Event CHANGE
    UINT32 pattern;                    // -Patro de filtratge
    bool state;                        // -Indicador ON/OFF
    bool posEdge;                      // -Indica si s'ha rebut un flanc positiu
    bool negEdge;                      // -Indica si s'ha rebut un flanc negatiu
} eosDigInput;

typedef struct __eosDigInputService {  // Dades del servei
    eosDigInputServiceState state;     // -Estat del servei
    bool haveChanges;                  // -Indica si hi han canvis
    eosDigInputHandle hFirstInput;     // -Primer element de la llista
} eosDigInputService;


static bool initialized = false;       // Controla singleton

static eosDigInputServiceHandle createDigInputServiceHandle(void);
static eosDigInputHandle createDigInputHandle(void);
static void tickFunction(eosDigInputServiceHandle hInput);


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosDigInputServiceHandle eosDigInputServiceInitialize(
 *               eosDigInputServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 *
 *************************************************************************/

eosDigInputServiceHandle eosDigInputServiceInitialize(
    eosDigInputServiceParams *params) {

    // Comprova que no estigui inicialitzat
    //
    if (initialized)
         return NULL;

    eosDigInputServiceHandle hService = createDigInputServiceHandle();
    if (!hService)
        return NULL;

    // Inicialitza les variables internes del servei
    //
    hService->state = serviceInitializing;
    hService->haveChanges = false;
    hService->hFirstInput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosTickRegisterCallback(NULL, (eosTickCallback) tickFunction, hService);

    initialized = true;

    return hService;
}


/************************************************************************
 *
 *       Comprova que el servei esta preparat i en funcionament
 *
 *       Funcio:
 *           bool eosDigInputServiceIsReady(
 *               eosDigInputServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           True si esta preparat. False en cas contrari
 *
 ************************************************************************/

bool __attribute__ ((always_inline)) eosDigInputServiceIsReady(
    eosDigInputServiceHandle hService) {

    return hService && (hService->state != serviceInitializing);
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosDigInputServiceTask(
 *               eosDigInputServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void eosDigInputServiceTask(
    eosDigInputServiceHandle hService) {

    switch (hService->state) {

        case serviceInitializing:
            hService->state = serviceRunning;
            break;

        case serviceRunning: {

            // Si no hi ha canvis, no cal procesar cap entrada,
            // aixi es guanya temps de proces
            //
            bool intState = eosInterruptDisable();
            bool haveChanges = hService->haveChanges;
            hService->haveChanges = false;
            eosInterruptRestore(intState);

            if (haveChanges) {
                eosDigInputHandle hInput = hService->hFirstInput;
                while (hInput) {

                    if (hInput->posEdge) {
                        if (hInput->onPosEdge != NULL) {
                            hInput->onPosEdge(hInput);
                            hInput->posEdge = FALSE;
                        }
                        else if (hInput->onChange != NULL) {
                            hInput->onChange(hInput);
                            hInput->posEdge = FALSE;
                        }
                    }

                    if (hInput->negEdge) {
                        if (hInput->onNegEdge != NULL) {
                            hInput->onNegEdge(hInput);
                            hInput->negEdge = FALSE;
                        }
                        else if (hInput->onChange != NULL) {
                            hInput->onChange(hInput);
                            hInput->negEdge = FALSE;
                        }
                    }

                    hInput = hInput->hNextInput;
                }
            }
            break;
        }
    }
}


/*************************************************************************
 *
 *       Crea una entrada
 *
 *       Funcio:
 *           eosDigInputHandle eosDigInputCreate(
 *               eosDigInoputServiceHandle hService,
 *               eosDigInputParams *params)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           params  : Parametres de la entrada
 *
 *       Retorn:
 *           El handler de la entrada
 *
 *************************************************************************/

eosDigInputHandle eosDigInputCreate(
    eosDigInputServiceHandle hService,
    eosDigInputParams *params) {

    eosDigInputHandle hInput = createDigInputHandle();
    if (hInput == NULL)
        return NULL;

    hInput->hService = hService;
    hInput->posEdge = false;
    hInput->negEdge = false;
    hInput->port = params->port;
    hInput->pin = params->pin;
    hInput->inverted = params->inverted;
    hInput->onPosEdge = params->onPosEdge;
    hInput->onNegEdge = params->onNegEdge;
    hInput->onChange = params->onChange;

    bool state = eosInterruptDisable();
    hInput->hNextInput = hService->hFirstInput;
    hService->hFirstInput = hInput;
    eosInterruptRestore(state);

    halPortSetupInput(hInput->port, hInput->pin);

    bool p = halPortGet(hInput->port, hInput->pin);
    hInput->state = hInput->inverted ? !p : p;

    if (hInput->state)
        hInput->pattern = 0xFFFFFFFF;
    else
        hInput->pattern = 0x00000000;

    return hInput;
}


/*************************************************************************
 *
 *       Destrueix una entrada
 *
 *       Funcio:
 *           void eosDigInputDestroy(
 *               eosDigInputHandle hInput)
 *
 *       Entrada:
 *          input: El handler de l'entrada
 *
 *************************************************************************/

void eosDigInputDestroy(
    eosDigInputHandle hInput) {
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           bool eosDigInputGet(
 *               eosDigInputHandle hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

bool __attribute__ ((always_inline)) eosDigInputGet(
    eosDigInputHandle hInput) {

    return hInput->state;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           bool eosDigInputPosEdge(
 *               eosDigInputHandle hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool eosDigInputPosEdge(
    eosDigInputHandle hInput) {

    if (hInput->posEdge) {
        hInput->posEdge = false;
        return true;
    }
    else
        return false;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc descendent (ON->OFF)
 *
 *       Funcio:
 *           bool eosDigInputNegEdge(
 *               eosDigInputHandle hInput)
 *
 *       Entrada:
 *           hInput: L'entrada
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool eosDigInputNegEdge(
    eosDigInputHandle hInput) {

    if (hInput->negEdge) {
        hInput->negEdge = false;
        return true;
    }
    else
        return false;
}


static eosDigInputServiceHandle createDigInputServiceHandle(void) {
    
    return (eosDigInputServiceHandle) eosAlloc(sizeof(eosDigInputService));
}


static eosDigInputHandle createDigInputHandle(void) {
    
    return (eosDigInputHandle) eosAlloc(sizeof(eosDigInput));
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void tickFunction(
 *               eosDigInputServiceHandle hService)
 *
 *       Entrada:
 *          hService: El handler del servei
 *
 *************************************************************************/

static void tickFunction(
    eosDigInputServiceHandle hService) {

    if (hService && (hService->state == serviceRunning)) {

        eosDigInputHandle hInput = hService->hFirstInput;
        while (hInput) {

            hInput->pattern <<= 1;

            bool p = halPortGet(hInput->port, hInput->pin);
            p = hInput->inverted ? !p : p;

            if (p)
                hInput->pattern |= 1;

            if ((hInput->pattern & PATTERN_MASK) == PATTERN_ON) {
                hInput->state = true;
                hInput->posEdge = true;
                hService->haveChanges = true;
            }
            else if ((hInput->pattern & PATTERN_MASK) == PATTERN_OFF) {
                hInput->state = false;
                hInput->negEdge = true;
                hService->haveChanges = true;
            }

            hInput = hInput->hNextInput;
        }
    }
}
