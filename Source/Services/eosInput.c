#include "Services/eosInput.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -En execucio
} eosInputServiceState;

#define PATTERN_ON       0x00007FFF
#define PATTERN_OFF      0x00008000
#define PATTERN_MASK     0x0000FFFF


typedef struct __eosInput {            // Dades d'una entrada
    eosInputServiceHandle hService;    // -El servei al que pertany
    eosInputHandle hNextInput;         // -Seguent element
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    bool inverted;                     // -Senyal invertida
    eosInputCallback onPosEdge;        // -Event POSEDGE
    eosInputCallback onNegEdge;        // -Event NEGEDGE
    eosInputCallback onChange;         // -Event CHANGE
    void *context;                     // -Parametre dels events
    UINT32 pattern;                    // -Patro de filtratge
    bool state;                        // -Indicador ON/OFF
    bool posEdge;                      // -Indica si s'ha rebut un flanc positiu
    bool negEdge;                      // -Indica si s'ha rebut un flanc negatiu
} eosInput;

typedef struct __eosInputService {     // Dades del servei
    eosInputServiceState state;        // -Estat del servei
    bool haveChanges;                  // -Indica si hi han canvis
    eosInputHandle hFirstInput;        // -Primer element de la llista
} eosInputService;


// Funcions d'acces al hardware
//
static void portInitialize(eosInputHandle hInput);
static bool portGet(eosInputHandle hInput);


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosInputServiceHandle eosInputServiceInitialize(
 *               eosInputServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del servei
 *
 *************************************************************************/

eosInputServiceHandle eosInputServiceInitialize(
    eosInputServiceParams *params) {

    eosInputServiceHandle hService = (eosInputServiceHandle) eosAlloc(sizeof(eosInputService));
    if (hService == NULL)
        return NULL;

    hService->state = serviceInitializing;
    hService->haveChanges = false;
    hService->hFirstInput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosTickServiceHandle hTickService = params->hTickService;
    if (hTickService == NULL)
        hTickService = eosGetTickServiceHandle();
    if (hTickService != NULL)
        eosTickAttach(hTickService, (eosTickCallback) eosInputServiceTick, hService);

    return hService;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosInputServiceTask(
 *               eosInputServiceHandle hService)
 * 
 *       Entrada:
 *           hService: El handler servei
 *
 *************************************************************************/

void eosInputServiceTask(
    eosInputServiceHandle hService) {

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
                eosInputHandle hInput = hService->hFirstInput;
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
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void eosInputServiceTick(
 *               eosInputServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler servei
 *
 *************************************************************************/

void eosInputServiceTick(
    eosInputServiceHandle hService) {

    if (hService->state == serviceRunning) {

        eosInputHandle hInput = hService->hFirstInput;
        while (hInput) {

            hInput->pattern <<= 1;
            if (portGet(hInput))
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


/*************************************************************************
 *
 *       Crea una entrada
 *
 *       Funcio:
 *           eosInputHandle eosInputCreate(
 *               eosInputServiceHandle hService,
 *               eosInputParams* params)
 *
 *       Entrada:
 *           hService: El servei
 *           params  : Parametres de la entrada
 *
 *       Retorn:
 *           El handler de la entrada
 *
 *************************************************************************/

eosInputHandle eosInputCreate(
    eosInputServiceHandle hService,
    eosInputParams* params) {

    eosInputHandle hInput = (eosInputHandle) eosAlloc(sizeof(eosInput));
    if (hInput == NULL)
        return NULL;

    hInput->hService = hService;
    hInput->posEdge = FALSE;
    hInput->negEdge = FALSE;
    hInput->channel = params->channel;
    hInput->position = params->position;
    hInput->inverted = params->inverted;
    hInput->onPosEdge = params->onPosEdge;
    hInput->onNegEdge = params->onNegEdge;
    hInput->onChange = params->onChange;

    bool state = eosInterruptDisable();
    hInput->hNextInput = hService->hFirstInput;
    hService->hFirstInput = hInput;
    eosInterruptRestore(state);

    portInitialize(hInput);
    hInput->state = portGet(hInput);
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
 *           void eosInputDestroy(
 *               eosInputHandle hInput)
 *
 *       Entrada:
 *          input: El handler de l'entrada
 *
 *************************************************************************/

void eosInputDestroy(
    eosInputHandle hInput) {
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           bool eosInputGet(
 *               eosInputHandle hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

bool __attribute__ ((always_inline)) eosInputGet(
    eosInputHandle hInput) {

    return hInput->state;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           bool eosInputPosEdge(
 *               eosInputHandle hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool eosInputPosEdge(
    eosInputHandle hInput) {

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
 *           bool eosInputNegEdge(
 *               eosInputHandle hInput)
 *
 *       Entrada:
 *           hInput: L'entrada
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool eosInputNegEdge(
    eosInputHandle hInput) {

    if (hInput->negEdge) {
        hInput->negEdge = false;
        return true;
    }
    else
        return false;
}


/*************************************************************************
 *
 *       Inicialitza el port d'entrada
 *
 *       Funcio:
 *           void portInitialize(
 *               eosInputHandle hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *************************************************************************/

static void portInitialize(
    eosInputHandle hInput) {

    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, hInput->channel, hInput->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port d'entrada
 *
 *       Funcio:
 *           bool portGet(
 *               eosInputHandle hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           Estat de la entrada
 *
 **************************************************************************/

static bool portGet(
    eosInputHandle hInput) {

    bool p = PLIB_PORTS_PinGet(PORTS_ID_0, hInput->channel, hInput->position);
    return hInput->inverted ? !p : p;
}
