#include "Services/eosDigInput.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "peripheral/ports/plib_ports.h"


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
    PORTS_CHANNEL channel;             // -Canal
    PORTS_BIT_POS position;                 // -Posicio
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


static eosDigInputServiceHandle __hService = NULL;


static void __tickFunction(eosDigInputServiceHandle hInput);


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

    if (__hService == NULL) {
        eosDigInputServiceHandle hService = eosAlloc(sizeof(eosDigInputService));
        if (hService != NULL) {

            hService->state = serviceInitializing;
            hService->haveChanges = false;
            hService->hFirstInput = NULL;
        
            eosTickRegisterCallback(NULL, (eosTickCallback) __tickFunction, hService, false);

            __hService = hService;
        }
    }

    return __hService;
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

bool eosDigInputServiceIsReady(
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
            bool lock = eosTickServiceLock();
            bool haveChanges = hService->haveChanges;
            hService->haveChanges = false;
            eosTickServiceUnlock(lock);

            if (haveChanges) {
                eosDigInputHandle hInput = hService->hFirstInput;
                while (hInput) {

                    if (hInput->posEdge) {
                        if (hInput->onPosEdge != NULL) {
                            hInput->onPosEdge(hInput);
                            hInput->posEdge = false;
                        }
                        else if (hInput->onChange != NULL) {
                            hInput->onChange(hInput);
                            hInput->posEdge = false;
                        }
                    }

                    if (hInput->negEdge) {
                        if (hInput->onNegEdge != NULL) {
                            hInput->onNegEdge(hInput);
                            hInput->negEdge = false;
                        }
                        else if (hInput->onChange != NULL) {
                            hInput->onChange(hInput);
                            hInput->negEdge = false;
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

    eosDigInputHandle hInput = eosAlloc(sizeof(eosDigInput));
    if (hInput != NULL) {

        hInput->hService = hService;
        hInput->posEdge = false;
        hInput->negEdge = false;
        hInput->channel = params->channel;
        hInput->position = params->position;
        hInput->inverted = params->inverted;
        hInput->onPosEdge = params->onPosEdge;
        hInput->onNegEdge = params->onNegEdge;
        hInput->onChange = params->onChange;

        bool lock = eosTickServiceLock();
        hInput->hNextInput = hService->hFirstInput;
        hService->hFirstInput = hInput;
        eosTickServiceUnlock(lock);

        if (true)
            PLIB_PORTS_ChangeNoticePullUpPerPortEnable(PORTS_ID_0, hInput->channel, hInput->position);
        PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, hInput->channel, hInput->position);

        bool p =  PLIB_PORTS_PinGet(PORTS_ID_0, hInput->channel, hInput->position);
        
        hInput->state = hInput->inverted ? !p : p;

        if (hInput->state)
            hInput->pattern = 0xFFFFFFFF;
        else
            hInput->pattern = 0x00000000;
    }
    
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

bool eosDigInputGet(
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


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void __tickFunction(
 *               eosDigInputServiceHandle hService)
 *
 *       Entrada:
 *          hService: El handler del servei
 *
 *************************************************************************/

static void __tickFunction(
    eosDigInputServiceHandle hService) {

    eosDigInputHandle hInput = hService->hFirstInput;
    while (hInput) {

        hInput->pattern <<= 1;

        bool p = PLIB_PORTS_PinGet(PORTS_ID_0, hInput->channel, hInput->position);
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
