#include "Services/__eosInputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "System/eosQueue.h"



static void enqueueEvent(eosInputService* service, eosInput* input, eosInputEvent event);
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

    // Crea la cua d'events
    //
    eosHandle hQueue;
    eosQueueCreateParams queueParams;
    queueParams.maxItems = params->maxEventQueue;
    queueParams.itemSize = sizeof(QueueItem);
    if (eosQueueCreate(&queueParams, &hQueue) != eos_RESULT_SUCCESS)
        return NULL;

    eosInputService* service = eosAlloc(sizeof(eosInputService));
    if (service) {

        service->state = SS_INITIALIZING;
        service->firstInput = NULL;
        service->hQueue = hQueue;

        // Asigna la funcio d'interrupcio TICK
        //
        eosHandle hTickService = params->hTickService;
        if (hTickService == NULL)
            hTickService = eosGetTickServiceHandle();
        if (hTickService != NULL)
            eosTickAttach(hTickService, eosInputServiceISRTick, (eosHandle) service, &service->hAttach);
        else
            service->hAttach = NULL;
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

            QueueItem item;
            BOOL intFlag, hasItems;

            do {

                intFlag = eosGetInterruptState();
                eosDisableInterrupts();
                hasItems = eosQueueGet(service->hQueue, &item) == eos_RESULT_SUCCESS;
                if (intFlag)
                    eosEnableInterrupts();

                if (hasItems) {
                    eosInputCallbackContext context;
                    context.context = item.input->context;
                    context.hService = (eosHandle) service;
                    context.hInput = (eosHandle) item.input;
                    context.event = item.event;
                    item.input->callback(&context);
                }

            } while (hasItems);
            
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
 *               void* context)
 *
 *       Entrada:
 *           context: El servei
 *
 *************************************************************************/

void eosInputServiceISRTick(void* context) {

#ifdef eos_OPTION_CheckInputParams
    if (context == NULL)
        return;
#endif

    eosInputService* service = (eosInputService*) context;
    if (service->state == serviceStateActive) {
        
        eosInput *input = service->firstInput;
        while (input) {

            input->pattern <<= 1;
            if (portGet(input))
                input->pattern |= 1;

            if ((input->pattern & PATTERN_MASK) == PATTERN_ON) {
                input->state = TRUE;
                input->posEdge = TRUE;
                if (input->callback && (input->callEvent == inputEventPosEdge))
                    enqueueEvent(service, input, inputEventPosEdge);
            }
            else if ((input->pattern & PATTERN_MASK) == PATTERN_OFF) {
                input->state = FALSE;
                input->negEdge = TRUE;
                if (input->callback && (input->callEvent == inputEventNegEdge))
                    enqueueEvent(service, input, inputEventNegEdge);
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
 *           eosInput* eosInputsCreate(
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

eosInput* eosInputsCreate(eosInputService* service, eosInputParams* params) {

    eosInput* input = eosAlloc(sizeof(eosInput));
    if (input) {
        input->posEdge = FALSE;
        input->negEdge = FALSE;
        input->channel = params->channel;
        input->position = params->position;
        input->inverted = params->inverted;
        input->callEvent = params->callEvent;
        input->callback = params->callback;
        input->context = params->context;
        input->service = service;
        input->nextInput = service->firstInput;
        service->firstInput = input;

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
 *           eosResult eosInputsDestroy(eosHandle hInput)
 *
 *       Entrada:
 *           hInput     : Handler de la entrada
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

void eosInputsDestroy(eosInput* input) {

}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           BOOL eosInputsGet(
 *               eosInput* input)
 *
 *       Entrada:
 *           input      : L'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

BOOL eosInputsGet(eosInput* input) {

    return input->state;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           BOOL eosInputsPosEdge(
 *               eosInput* input)
 *
 *       Entrada:
 *           input      : L'entrada
 *
 *       Retorn:
 *           TRUS s' s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputsPosEdge(eosInput* input) {

    BOOL result = input->posEdge;
    input->posEdge = FALSE;
    return result;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc descendent (ON->OFF)
 *
 *       Funcio:
 *           BOOL eosInputsNegEdge(
 *               eosInput* input)
 *
 *       Entrada:
 *           input      : L'entrada
 *
 *       Retorn:
 *           TRUS s' s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputsNegEdge(eosInput* input) {

    BOOL result = input->negEdge;
    input->negEdge = FALSE;
    return result;
}


/*************************************************************************
 *
 *       Afegeix un event en la cua
 *
 *       Funcio:
 *           void enqueueEvent(
 *               eosInputService* service,
 *               eosInput* input,
 *               eosInputEvent event)
 *
 *       Entrada:
 *           service    : Dades del servei
 *           input      : Dades de l'entrada
 *           event      : Event a procesar
 *
 *************************************************************************/

static void enqueueEvent(eosInputService* service, eosInput* input, eosInputEvent event) {

    QueueItem item;
    item.input = input;
    item.event = event;

    eosQueuePut(service->hQueue, &item);
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
