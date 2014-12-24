#include "Services/eosInputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -En execucio
} ServiceStates;

#define PATTERN_ON       0x00007FFF
#define PATTERN_OFF      0x00008000
#define PATTERN_MASK     0x0000FFFF


typedef struct __eosInput {            // Dades d'una entrada
    eosHInputService hService;         // -El servei al que pertany
    eosHInput hNextInput;              // -Seguent element
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
} Input;

typedef struct __eosInputService {     // Dades del servei
    ServiceStates state;               // -Estat del servei
    eosHInput hFirstInput;             // -Primer element de la llista
} InputService;


// Funcions d'acces al hardware
//
static void halPortInitialize(eosHInput hInput);
static bool halPortGet(eosHInput hInput);


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosHInputService eosInputServiceInitialize(
 *               eosInputServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del servei
 *
 *************************************************************************/

eosHInputService eosInputServiceInitialize(
    eosInputServiceParams *params) {

    eosHInputService hService = (eosHInputService) eosAlloc(sizeof(InputService));
    if (hService == NULL)
        return NULL;

    hService->state = serviceInitializing;
    hService->hFirstInput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosHTickService hTickService = params->hTickService;
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
 *               eosHInputService hService)
 * 
 *       Entrada:
 *           hService: El handler servei
 *
 *************************************************************************/

void eosInputServiceTask(
    eosHInputService hService) {

    switch (hService->state) {
        case serviceInitializing:
            hService->state = serviceRunning;
            break;

        case serviceRunning: {
            eosHInput hInput = hService->hFirstInput;
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
 *               eosHInputService hService)
 *
 *       Entrada:
 *           hSservice: El handler servei
 *
 *************************************************************************/

void eosInputServiceTick(
    eosHInputService hService) {

    if (hService->state == serviceRunning) {       
        eosHInput hInput = hService->hFirstInput;
        while (hInput) {

            hInput->pattern <<= 1;
            if (halPortGet(hInput))
                hInput->pattern |= 1;

            if ((hInput->pattern & PATTERN_MASK) == PATTERN_ON) {
                hInput->state = TRUE;
                hInput->posEdge = TRUE;
            }
            else if ((hInput->pattern & PATTERN_MASK) == PATTERN_OFF) {
                hInput->state = FALSE;
                hInput->negEdge = TRUE;
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
 *           eosHInpot eosInputCreate(
 *               eosHInputService hService,
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

eosHInput eosInputCreate(
    eosHInputService hService,
    eosInputParams* params) {

    eosHInput hInput = (eosHInput) eosAlloc(sizeof(Input));
    if (hInput == NULL)
        return NULL;

    hInput->posEdge = FALSE;
    hInput->negEdge = FALSE;
    hInput->channel = params->channel;
    hInput->position = params->position;
    hInput->inverted = params->inverted;
    hInput->onPosEdge = params->onPosEdge;
    hInput->onNegEdge = params->onNegEdge;
    hInput->onChange = params->onChange;

    bool intFlag = eosGetInterruptState();
    eosDisableInterrupts();

    hInput->hService = hService;
    hInput->hNextInput = hService->hFirstInput;
    hService->hFirstInput = hInput;

    if (intFlag)
        eosEnableInterrupts();

    halPortInitialize(hInput);
    hInput->state = halPortGet(hInput);
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
 *               eosHInput hInput)
 *
 *       Entrada:
 *          input: El handler de l'entrada
 *
 *************************************************************************/

void eosInputDestroy(
    eosHInput hInput) {
/*
    eosHInputService hService = hInput->hService;
    
    eosHInput hCurrentInput = hService->hFirstInput;
    eosHInput hPrevInput = NULL;
    while (hCurrentInput) {
        if (hCurrentInput == hInput) {
            if (hPrevInput)
                hPrevInput->hNextInput = hCurrentInput->hNextInput;
            else
                hService->hFirstInput = hCurrentInput->hNextInput;
            eosFree(hInput);
            return;

        }

        hPrevInput = hCurrentInput;
        hCurrentInput = hCurrentInput->hNextInput;
    }*/
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           bool eosInputGet(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

bool eosInputGet(
    eosHInput hInput) {

    return hInput->state;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           bool eosInputPosEdge(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           TRUE si s'ha produit el flanc
 *
 *************************************************************************/

bool eosInputPosEdge(
    eosHInput hInput) {

    bool result = hInput->posEdge;
    hInput->posEdge = FALSE;
    return result;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc descendent (ON->OFF)
 *
 *       Funcio:
 *           bool eosInputNegEdge(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: L'entrada
 *
 *       Retorn:
 *           TRUE si s'ha produit el flanc
 *
 *************************************************************************/

bool eosInputNegEdge(
    eosHInput hInput) {

    bool result = hInput->negEdge;
    hInput->negEdge = FALSE;
    return result;
}


/*************************************************************************
 *
 *       Inicialitza el port d'entrada
 *
 *       Funcio:
 *           void halPortInitialize(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *************************************************************************/

static void halPortInitialize(
    eosHInput hInput) {

    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, hInput->channel, hInput->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port d'entrada
 *
 *       Funcio:
 *           bool halPortGet(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           Estat de la entrada
 *
 **************************************************************************/

static bool halPortGet(
    eosHInput hInput) {

    bool p = PLIB_PORTS_PinGet(PORTS_ID_0, hInput->channel, hInput->position);
    return hInput->inverted ? !p : p;
}
