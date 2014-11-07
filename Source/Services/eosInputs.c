#define __EOS_INPUTS_INTERNAL
#include "Services/eosInputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


typedef enum {
    state_Initializing,                // Inicialitzant
    state_Running                      // En execucio
} States;

#define PATTERN_ON       0x00007FFF
#define PATTERN_OFF      0x00008000
#define PATTERN_MASK     0x0000FFFF


typedef struct __eosInput {            // Dades d'una entrada
    eosHInputService hService;         // -El servei al que pertany
    eosHInput hNextInput;              // -Seguent entrada
    PORTS_CHANNEL channel;             // -Canal del port
    PORTS_BIT_POS position;            // -Pin del port
    BOOL inverted;                     // -Senyal invertida;
    unsigned when;                     // -Quant hi ha que executar la funcio callback
    eosCallback callback;              // -Funcio callback
    void *context;                     // -Parametre de la funcio callback
    UINT32 pattern;                    // -Patro de filtratge
    BOOL state;                        // -Indicador ON/OFF
    BOOL posEdge;                      // -Indica si s'ha rebut un falc positiu
    BOOL negEdge;                      // -Indica si s'ha rebut un flanc negatiu
} Input;

typedef struct __eosInputService {     // Dades del servei
    States state;                      // -Estat del servei
    eosHInput hFirstInput;             // -Primera entrada de la llista
} InputService;


static void portInitialize(eosHInput hInput);
static BOOL portGet(eosHInput hInput);


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosResult eosInputServiceInitialize(
 *               eosInputServiceParams *params,
 *               eosHInputService hService)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Sortida:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosInputServiceInitialize(
    eosInputServiceParams *params,
    eosHInputService *_hService) {

    eosHInputService hService = eosAlloc(sizeof(InputService));
    if (hService == NULL)
        return eos_ERROR_ALLOC;

    hService->state = state_Initializing;
    hService->hFirstInput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosHTickService hTickService = params->hTickService;
    if (hTickService == NULL)
        hTickService = eosGetTickServiceHandle();
    if (hTickService != NULL)
        eosTickAttach(hTickService, (eosCallback) eosInputServiceISRTick, hService);

    *_hService = hService;
   
    return eos_RESULT_SUCCESS;
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
        case state_Initializing:
            hService->state = state_Running;
            break;

        case state_Running: {

            eosHInput hInput = hService->hFirstInput;
            while (hInput) {

                if ((hInput->posEdge && hInput->when == INPUT_ON_POSEDGE) ||
                    (hInput->negEdge && hInput->when == INPUT_ON_NEGEDGE)) {

                    eosInputCallbackContext context;
                    context.hService = hService;
                    context.hInput = hInput;
                    context.when = hInput->when;
                    context.context = hInput->context;
                    hInput->callback(&context);
                    hInput->posEdge = FALSE;
                    hInput->negEdge = FALSE;
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
 *           void eosInputServiceISRTick(
 *               eosHInputService hService)
 *
 *       Entrada:
 *           hSservice: El handler servei
 *
 *************************************************************************/

void eosInputServiceISRTick(
    eosHInputService hService) {

    if (hService->state == state_Running) {
        
        eosHInput hInput = hService->hFirstInput;
        while (hInput) {

            hInput->pattern <<= 1;
            if (portGet(hInput))
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
 *           eosResult eosInputCreate(
 *               eosHInputService hService,
 *               eosInputParams* params,
 *               eosHInput *hInput)
 *
 *       Entrada:
 *           hService: El servei
 *           params  : Parametres de la entrada
 *
 *       Sortida:
 *           hInput: El handler de la entrada
 *
 *       Retorn:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosInputCreate(
    eosHInputService hService,
    eosInputParams* params,
    eosHInput *_hInput) {

    eosHInput hInput = eosAlloc(sizeof(struct __eosInput));
    if (hInput == NULL)
        return eos_ERROR_ALLOC;

    hInput->posEdge = FALSE;
    hInput->negEdge = FALSE;
    hInput->channel = params->channel;
    hInput->position = params->position;
    hInput->inverted = params->inverted;
    hInput->when = params->when;
    hInput->callback = params->callback;
    hInput->context = params->context;

    BOOL intFlag = eosGetInterruptState();
    eosDisableInterrupts();

    hInput->hService = hService;
    hInput->hNextInput = hService->hFirstInput;
    hService->hFirstInput = hInput;

    if (intFlag)
        eosEnableInterrupts();

    portInitialize(hInput);
    hInput->state = portGet(hInput);
    if (hInput->state)
        hInput->pattern = 0xFFFFFFFF;
    else
        hInput->pattern = 0x00000000;

    *_hInput = hInput;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix una entrada
 *
 *       Funcio:
 *           eosResult eosInputDestroy(
 *               eosHInput hInput)
 *
 *       Entrada:
 *          input: El handler de l'entrada
 *
 *************************************************************************/

eosResult eosInputDestroy(
    eosHInput hInput) {

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           BOOL eosInputGet(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

BOOL eosInputGet(
    eosHInput hInput) {

    return hInput->state;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           BOOL eosInputPosEdge(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           TRUE si s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputPosEdge(
    eosHInput hInput) {

    BOOL result = hInput->posEdge;
    hInput->posEdge = FALSE;
    return result;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc descendent (ON->OFF)
 *
 *       Funcio:
 *           BOOL eosInputNegEdge(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: L'entrada
 *
 *       Retorn:
 *           TRUE si s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputNegEdge(
    eosHInput hInput) {

    BOOL result = hInput->negEdge;
    hInput->negEdge = FALSE;
    return result;
}


/*************************************************************************
 *
 *       Inicialitza el port d'entrada
 *
 *       Funcio:
 *           void portInitialize(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *************************************************************************/

static void portInitialize(
    eosHInput hInput) {

    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, hInput->channel, hInput->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port d'entrada
 *
 *       Funcio:
 *           BOOL portGet(
 *               eosHInput hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           Estat de la entrada
 *
 **************************************************************************/

static BOOL portGet(
    eosHInput hInput) {

    BOOL p = PLIB_PORTS_PinGet(PORTS_ID_0, hInput->channel, hInput->position);
    return hInput->inverted ? !p : p;
}
