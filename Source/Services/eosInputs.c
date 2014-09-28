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
    BOOL inverted;           // -Senyal invertida;
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
    eosHandle hTickService;  // -Servei TICK
    eosHandle hQueue;        // -Cua d'events
    PInput inputs;           // -Llista d'entrades
    BOOL terminate;          // -Indica si cal finalitzar el servei
} Service, *PService;

typedef struct {             // Element de la cua d'events
    PInput input;            // -Dades de l'entrada
    eosInputEvent event;     // -Tipus d'event
} QueueItem;


static void enqueueEvent(PService service, PInput input, eosInputEvent event);
static void portInitialize(PInput input);
static BOOL portGet(PInput input);


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
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
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
        return eos_ERROR_ALLOC;
    }

    // Inicialitza les estructures de dades
    //
    service->state = serviceStateInitialize;
    service->maxInputs = params->maxInputs;
    service->inputs = inputs;
    service->hQueue = hQueue;
    service->hTickService = params->hTickService;
    service->terminate = FALSE;

    unsigned i;
    for (i = 0; i < service->maxInputs; i++)
        service->inputs[i].active = FALSE;

    // Asigna la funcio d'interrupcio TICK
    //
    if (service->hTickService)
        eosTickAttach(service->hTickService, eosInputsISRTick, (eosHandle) service);

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

    // Desasigna la funcio d'interrupcio TICK
    //
    if (service->hTickService)
        eosTickDeattach(service->hTickService, eosInputsISRTick);

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
    if (service->state == serviceStateActive) {
        
        unsigned i;
        for (i = 0; i < service->maxInputs; i++) {
            PInput input = &service->inputs[i];
            if (input->active) {

                input->pattern <<= 1;
                if (portGet(input))
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
}


/*************************************************************************
 *
 *       Crea una entrada
 *
 *       Funcio:
 *           eosResult eosInputsCreate(
 *               eosHandle hService,
 *               eosInputsCreateParams *params,
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

eosResult eosInputsCreate(eosHandle hService, eosInputsCreateParams *params, eosHandle *hInput) {

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
            input->posEdge = FALSE;
            input->negEdge = FALSE;
            input->channel = params->channel;
            input->position = params->position;
            input->inverted = params->inverted;
            input->callOn = params->callOn;
            input->callback = params->callback;
            input->context = params->context;

            portInitialize(input);
            input->state = portGet(input);
            if (input->state)
                input->pattern = 0xFFFFFFFF;
            else
                input->pattern = 0x00000000;

            *hInput = (eosHandle) input;
            break;
        }
    }
    if (i == service->maxInputs)
        return eos_ERROR_OPERATION;

    return eos_RESULT_SUCCESS;
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

eosResult eosInputsDestroy(eosHandle hInput) {

    if (hInput == NULL)
        return eos_ERROR_PARAM_NULL;

    PInput input = (PInput) hInput;
    input->active = FALSE;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           BOOL eosInputsGet(eosHandle hInput)
 *
 *       Entrada:
 *           hInput     : handler de l'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

BOOL eosInputsGet(eosHandle hInput) {

    if (hInput == NULL)
        return FALSE;

    PInput input = (PInput) hInput;
    return input->state;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           BOOL eosInputsPosEdge(eosHandle hInput)
 *
 *       Entrada:
 *           hInput     : Handler de l'entrada
 *
 *       Retorn:
 *           TRUS s' s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputsPosEdge(eosHandle hInput) {

    if (hInput == NULL)
        return FALSE;

    PInput input = (PInput) hInput;
    BOOL result = input->posEdge;
    input->posEdge = FALSE;
    return result;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc descendent (ON->OFF)
 *
 *       Funcio:
 *           BOOL eosInputsNegEdge(eosHandle hInput)
 *
 *       Entrada:
 *           hInput     : Handler de l'entrada
 *
 *       Retorn:
 *           TRUS s' s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputsNegEdge(eosHandle hInput) {

    if (hInput == NULL)
        return FALSE;

    PInput input = (PInput) hInput;
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
 *       Inicialitza el port d'entrada
 *
 *       Funcio:
 *           void portInitialize(PInput input)
 *
 *       Entrada:
 *           input      : Dades de l'entrada
 *
 *************************************************************************/

static void portInitialize(PInput input) {

    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, input->channel, input->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port d'entrada
 *
 *       Funcio:
 *           BOOL portGet(PInput input)
 *
 *       Entrada:
 *           input      : Dades de l'entrada
 *
 *       Retorn:
 *           Estat de la entrada
 *
 **************************************************************************/

static BOOL portGet(PInput input) {

    BOOL p = PLIB_PORTS_PinGet(PORTS_ID_0, input->channel, input->position);
    return input->inverted ? !p : p;
}