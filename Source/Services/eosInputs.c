#include "Services/__eosInputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


static void portInitialize(eosInput* input);
static BOOL portGet(eosInput* input);


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosInputService* eosInputServiceInitialize(
 *               eosInputServiceParams *params)
 *
 *       Entrada:
 *           params     : Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El servei, NULL en cas d'error
 *
 *************************************************************************/

eosInputService* eosInputServiceInitialize(eosInputServiceParams *params) {

    eosInputService* service = eosAlloc(sizeof(eosInputService));
    if (service) {

        service->state = SS_INITIALIZING;
        service->firstInput = NULL;

        // Asigna la funcio d'interrupcio TICK
        //
        eosTickService* tickService = params->tickService;
        if (tickService == NULL)
            tickService = eosGetTickServiceHandle();
        if (tickService != NULL)
            eosTickAttach(tickService, (eosCallback) eosInputServiceISRTick, (void*) service);
    }
    
    return service;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosInputServiceTask(
 *               eosInputService* service)
 * 
 *       Entrada:
 *           hService   : Handler del servei
 *
 *************************************************************************/

void eosInputServiceTask(eosInputService* service) {

    switch (service->state) {
        case SS_INITIALIZING:
            service->state = SS_RUNNING;
            break;

        case SS_RUNNING: {

            eosInput* input = service->firstInput;
            while (input) {

                if ((input->posEdge && input->when == INPUT_ON_POSEDGE) ||
                    (input->negEdge && input->when == INPUT_ON_NEGEDGE)) {

                    eosInputCallbackContext context;
                    context.service = service;
                    context.input = input;
                    context.when = input->when;
                    context.context = input->context;
                    input->callback(&context);
                    input->posEdge = FALSE;
                    input->negEdge = FALSE;
                }

                input = input->nextInput;
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
 *               eosInputService *service)
 *
 *       Entrada:
 *           service: El servei
 *
 *************************************************************************/

void eosInputServiceISRTick(eosInputService *service) {

    if (service->state == SS_RUNNING) {
        
        eosInput *input = service->firstInput;
        while (input) {

            input->pattern <<= 1;
            if (portGet(input))
                input->pattern |= 1;

            if ((input->pattern & PATTERN_MASK) == PATTERN_ON) {
                input->state = TRUE;
                input->posEdge = TRUE;
            }
            else if ((input->pattern & PATTERN_MASK) == PATTERN_OFF) {
                input->state = FALSE;
                input->negEdge = TRUE;
            }

            input = input->nextInput;
        }
    }
}


/*************************************************************************
 *
 *       Crea una entrada
 *
 *       Funcio:
 *           eosInput* eosInputCreate(
 *               eosInputService* service,
 *               eosInputParams* params)
 *
 *       Entrada:
 *           service    : El servei
 *           params     : Parametres de la entrada
 *
 *       Retorn:
 *           La entrada, NULL en cas d'error
 *
 *************************************************************************/

eosInput* eosInputCreate(eosInputService* service, eosInputParams* params) {

    eosInput* input = eosAlloc(sizeof(eosInput));
    if (input) {
        input->posEdge = FALSE;
        input->negEdge = FALSE;
        input->channel = params->channel;
        input->position = params->position;
        input->inverted = params->inverted;
        input->when = params->when;
        input->callback = params->callback;
        input->context = params->context;

        BOOL intFlag = eosGetInterruptState();
        eosDisableInterrupts();

        input->service = service;
        input->nextInput = service->firstInput;
        service->firstInput = input;

        if (intFlag)
            eosEnableInterrupts();

        portInitialize(input);
        input->state = portGet(input);
        if (input->state)
            input->pattern = 0xFFFFFFFF;
        else
            input->pattern = 0x00000000;
    }

    return input;
}


/*************************************************************************
 *
 *       Destrueix una entrada
 *
 *       Funcio:
 *           void eosInputDestroy(
 *               eosInput* input)
 *
 *       Entrada:
 *          input       : L'entrada
 *
 *************************************************************************/

void eosInputDestroy(eosInput* input) {

}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           BOOL eosInputGet(
 *               eosInput* input)
 *
 *       Entrada:
 *           input      : L'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

BOOL eosInputGet(eosInput* input) {

    return input->state;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           BOOL eosInputPosEdge(
 *               eosInput* input)
 *
 *       Entrada:
 *           input      : L'entrada
 *
 *       Retorn:
 *           TRUS si s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputPosEdge(eosInput* input) {

    BOOL result = input->posEdge;
    input->posEdge = FALSE;
    return result;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc descendent (ON->OFF)
 *
 *       Funcio:
 *           BOOL eosInputNegEdge(
 *               eosInput* input)
 *
 *       Entrada:
 *           input      : L'entrada
 *
 *       Retorn:
 *           TRUS si s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputNegEdge(eosInput* input) {

    BOOL result = input->negEdge;
    input->negEdge = FALSE;
    return result;
}


/*************************************************************************
 *
 *       Inicialitza el port d'entrada
 *
 *       Funcio:
 *           void portInitialize(
 *               eosInput* input)
 *
 *       Entrada:
 *           input      : Dades de l'entrada
 *
 *************************************************************************/

static void portInitialize(eosInput* input) {

    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, input->channel, input->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port d'entrada
 *
 *       Funcio:
 *           BOOL portGet(
 *               eosInput* input)
 *
 *       Entrada:
 *           input      : Dades de l'entrada
 *
 *       Retorn:
 *           Estat de la entrada
 *
 **************************************************************************/

static BOOL portGet(eosInput* input) {

    BOOL p = PLIB_PORTS_PinGet(PORTS_ID_0, input->channel, input->position);
    return input->inverted ? !p : p;
}

