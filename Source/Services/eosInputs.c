#include "Services/eosInputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "System/eosQueue.h"


#define PATTERN_ON           0x00007FFF
#define PATTERN_OFF          0x00008000
#define PATTERN_MASK         0x0000FFFF


typedef struct {             // Dates d'una entrada
    BOOL active;             // -Indica si esta actiu
    PORTS_CHANNEL channel;   // -Canal del port
    PORTS_BIT_POS position;  // -Pin del port
    eosInputEvent callOn;    // -Modus de crida
    eosCallback callback;    // -Funcio callback
    void *context;           // -Parametre de la funcio callback
    UINT32 pattern;          // -Patro de filtratge
    BOOL state;              // -Indicador ON/OFF
    BOOL posEdge;            // -Indica si s'ha rebut un falc positiu
    BOOL negEdge;            // -Indica si s'ha rebut un flanc negatiu
} Input, *PInput;

typedef enum {               // Estat del servei
    serviceStateInitialize,  // -Inicialitza
    serviceStateTerminate,   // -Finalitza
    serviceStateActive       // -Actiu
} ServiceState;

typedef struct {             // Dades del servei
    ServiceState state;      // -Estat del servei
    unsigned maxInputs;      // -Numero maxim d'entrades a gestionar
    eosHandle hQueue;        // -Cua d'events
    PInput inputs;           // -Llista d'entrades
    BOOL terminate;          // -Indica si cal finalitzar el servei
} Service, *PService;

typedef struct {
    PInput input;
    eosInputEvent event;
} QueueItem;


static BOOL hasEvents(PService service);
static void throwEvent(PService service);
static void enqueueEvent(PService service, PInput input, eosInputEvent event);


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosResult eosInputsInitialize(
 *               eosInputsInitializeParams *params,
 *               eosHandle *hService)
 *
 *       Entrada:
 *           params     : Parametres d'inicialitzacio
 *
 *       Sortida:
 *           hService   : El handler del servei
 *
 *       Retorn:
 *           eos_RETURN_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosInputsInitialize(eosInputsInitializeParams *params, eosHandle *hService) {

    // Comprova els parametres
    //
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;

    // Crea les estructures de dades en el HEAP
    //
    PService service = eosAlloc(sizeof(Service));
    if (service == NULL)
        return eos_ERROR_ALLOC;

    PInput inputs = eosAlloc(sizeof(Input) * params->maxInputs);
    if (inputs == NULL) {
        eosFree(service);
        return eos_ERROR_ALLOC;
    }

    // Crea la cua d'events
    //
    eosHandle hQueue;
    eosQueueCreateParams queueParams;
    queueParams.maxItems = params->maxEventQueue;
    queueParams.size = sizeof(QueueItem);
    if (eosQueueCreate(&queueParams, &hQueue) != eos_RESULT_SUCCESS) {
        eosFree(inputs);
        eosFree(service);
        return eos_ERROR_OPERATION;
    }

    // Inicialitza les estructures de dades
    //
    service->state = serviceStateInitialize;
    service->maxInputs = params->maxInputs;
    service->inputs = inputs;
    service->hQueue = hQueue;
    service->terminate = FALSE;

    unsigned i;
    for (i = 0; i < service->maxInputs; i++)
        service->inputs[i].active = FALSE;

    // Asigna la funcio d'interrupcio TICK
    //
    if (params->hTickService)
        eosTickAttach(params->hTickService, eosInputsISRTick, (eosHandle) service);

    // Retorna resultats i finalitza
    //
    *hService = (eosHandle) service;
    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Finalitza el servei
 *
 *       Funcio:
 *           eosResult eosInputsTerminate(
 *               eosHandle hService)
 *
 *       Entrada:
 *           hService   : Handler del servei
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosInputsTerminate(eosHandle hService) {

    // Comprova els parametres
    //
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;

    PService service = (PService) hService;

    // Notifica el final i espera que finalitzi
    //
    service->terminate = TRUE;
    while (service->state != serviceStateTerminate)
        eosTimerTask(hService);

    // Allibera la memoria de les estructures de dades
    //
    eosQueueDestroy(service->hQueue);
    eosFree(service->inputs);
    eosFree(service);

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           eosResult eosInputsTask(
 *               eosHandle hService)
 * 
 *       Entrada:
 *           hService   : Handler del servei
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosInputsTask(eosHandle hService) {

    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;

    PService service = (PService) hService;

    switch (service->state) {
        case serviceStateInitialize:
            service->state = serviceStateActive;
            break;

        case serviceStateActive: {

            while (hasEvents(service))
                throwEvent(service);
            
            if (service->terminate)
                service->state = serviceStateTerminate;
            break;
        }

        case serviceStateTerminate:
            break;
    }

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Gestiona la interrupcio TICK
 *
 *       Funcio:
 *           void eosInputsISRTick(void *context)
 *
 *       Entrada:
 *           context: Handler del sevei
 *
 *************************************************************************/

void eosInputsISRTick(void *context) {

    if (context == NULL)
        return;

    PService service = (PService) context;
   
    unsigned i;
    for (i = 0; i < service->maxInputs; i++) {
        PInput input = &service->inputs[i];
        if (input->active) {

            input->pattern <<= 1;
            if (PLIB_PORTS_PinGet(PORTS_ID_0, input->channel, input->position))
                input->pattern |= 1;

            if ((input->pattern & PATTERN_MASK) == PATTERN_ON) {
                input->state = TRUE;
                input->posEdge = TRUE;
                if (input->callback && (input->callOn == inputEventPosEdge))
                    enqueueEvent(service, input, inputEventPosEdge);
            }
            else if ((input->pattern & PATTERN_MASK) == PATTERN_OFF) {
                input->state = FALSE;
                input->negEdge = TRUE;
                if (input->callback && (input->callOn == inputEventNegEdge))
                    enqueueEvent(service, input, inputEventNegEdge);
            }
        }
    }
}


/*************************************************************************
 *
 *       Crea una entrada
 *
 *       Funcio:
 *           eosResult eosInputsCreate(
 *               eosHandle hService,
 *               eosInputCreateParams *params,
 *               eosHandle *hInput)
 *
 *       Entrada:
 *           hService   : Handler del servei
 *           params     : Parametres de la entrada
 *
 *       Sortida:
 *           hInput     : Handler de l'entrada
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosInputsCreate(eosHandle hService, eosInputCreateParams *params, eosHandle *hInput) {

    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
    if (hInput == NULL)
        return eos_ERROR_PARAM_NULL;

    PService service = (PService) hService;

    unsigned i;
    for (i = 0; i < service->maxInputs; i++) {
        PInput input = &service->inputs[i];
        if (!input->active) {
            input->active = TRUE;
            input->state = FALSE;
            input->posEdge = FALSE;
            input->negEdge = FALSE;
            input->channel = params->channel;
            input->position = params->position;
            input->callOn = params->callOn;
            input->callback = params->callback;
            input->context = params->context;

            PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, params->channel, params->position);

            *hInput = (eosHandle) input;
            break;
        }
    }
    if (i == service->maxInputs)
        return eos_ERROR_OPERATION;

    return eos_RESULT_SUCCESS;
}


eosResult eosInputsDestroy(eosHandle hInput) {

    if (hInput == NULL)
        return eos_ERROR_PARAM_NULL;

    PInput input = (PInput) hInput;
    input->active = FALSE;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa un event de la cua
 * 
 *       Funcio:
 *           void throwEvent(
 *               PService service,
 *
 *       Entrada:
 *           service    : Dades del servei
 *
 *       Notes:
 *           No fa cap verificacio d'errors
 *
 *************************************************************************/

static void throwEvent(PService service) {

    QueueItem item;
    eosQueueGet(service->hQueue, &item);

    eosInputCallbackContext context;
    context.context = item.input->context;
    context.hService = (eosHandle) service;
    context.hInput = (eosHandle) item.input;
    context.event = item.event;
    item.input->callback(&context);
}


/*************************************************************************
 *
 *       Afegeix un event en la cua
 *
 *       Funcio:
 *           void enqueueEvent(
 *               PService service,
 *               PInput input,
 *               eosInputEvent event)
 *
 *       Entrada:
 *           service    : Dades del servei
 *           input      : Dades de l'entrada
 *           event      : Event a procesar
 *
 *************************************************************************/

static void enqueueEvent(PService service, PInput input, eosInputEvent event) {

    QueueItem item;
    item.input = input;
    item.event = event;
    eosQueuePut(service->hQueue, &item);
}


/*************************************************************************
 *
 *       Comprova si hi han event en la cua
 *
 *       Funcio:
 *           BOOL hasEvents(PService service)
 *
 *       Entrada:
 *           service    : Dades del servei
 *
 *       Retorn:
 *           TRUE si queda quelcom en la cua
 *
 *************************************************************************/

static BOOL hasEvents(PService service) {

    BOOL isEmpty;
    return (eosQueueGetIsEmpty(service->hQueue, &isEmpty) == eos_RESULT_SUCCESS) && !isEmpty;
}