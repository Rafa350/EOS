#include "Services/eosOutputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "System/eosQueue.h"


typedef struct {             // Dates d'una entrada
    BOOL active;             // -Indica si esta actiu
    PORTS_CHANNEL channel;   // -Canal del port
    PORTS_BIT_POS position;  // -Pin del port
    BOOL inverted;           // -Senyal invertida;
} Output, *POutput;

typedef enum {               // Estat del servei
    serviceStateInitialize,  // -Inicialitza
    serviceStateTerminate,   // -Finalitza
    serviceStateActive       // -Actiu
} ServiceState;

typedef struct {             // Dades del servei
    ServiceState state;      // -Estat del servei
    unsigned maxOutputs;     // -Numero maxim d'entrades a gestionar
    POutput outputs;         // -Llista de sortides
    BOOL terminate;          // -Indica si cal finalitzar el servei
} Service, *PService;


static void portInitialize(POutput output);
static BOOL portGet(POutput output);
static void portSet(POutput output, BOOL state);


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosResult eosOutputsInitialize(
 *               eosOutputsInitializeParams *params,
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

eosResult eosOutputsInitialize(eosOutputsInitializeParams *params, eosHandle *hService) {

    // Comprova els parametres
    //
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;

    // Crea les estructures de dades en el HEAP
    //
    PService service = eosAlloc(sizeof(Service));
    if (service == NULL)
        return eos_ERROR_ALLOC;

    POutput outputs = eosAlloc(sizeof(Output) * params->maxOutputs);
    if (outputs == NULL) {
        eosFree(service);
        return eos_ERROR_ALLOC;
    }

    // Inicialitza les estructures de dades
    //
    service->state = serviceStateInitialize;
    service->maxOutputs = params->maxOutputs;
    service->outputs = outputs;
    service->terminate = FALSE;

    unsigned i;
    for (i = 0; i < service->maxOutputs; i++)
        service->outputs[i].active = FALSE;

    // Asigna la funcio d'interrupcio TICK
    //
    if (params->hTickService)
        eosTickAttach(params->hTickService, eosOutputsISRTick, (eosHandle) service);

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
 *           eosResult eosOutputdTerminate(
 *               eosHandle hService)
 *
 *       Entrada:
 *           hService   : Handler del servei
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosOutputsTerminate(eosHandle hService) {

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
    eosFree(service->outputs);
    eosFree(service);

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           eosResult eosOutputsTask(
 *               eosHandle hService)
 * 
 *       Entrada:
 *           hService   : Handler del servei
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosOutputsTask(eosHandle hService) {

    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;

    PService service = (PService) hService;

    switch (service->state) {
        case serviceStateInitialize:
            service->state = serviceStateActive;
            break;

        case serviceStateActive: {

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
 *           void eosOutputsISRTick(void *context)
 *
 *       Entrada:
 *           context: Handler del sevei
 *
 *************************************************************************/

void eosOutputsISRTick(void *context) {

    if (context == NULL)
        return;

    PService service = (PService) context;
    if (service->state == serviceStateActive) {
    }
}


/*************************************************************************
 *
 *       Crea una sortida
 *
 *       Funcio:
 *           eosResult eosOutputsCreate(
 *               eosHandle hService,
 *               eosOutputsCreateParams *params,
 *               eosHandle *hInput)
 *
 *       Entrada:
 *           hService   : Handler del servei
 *           params     : Parametres de la sortida
 *
 *       Sortida:
 *           hOutput    : Handler de la sortida
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosOutputsCreate(eosHandle hService, eosOutputsCreateParams *params, eosHandle *hOutput) {

    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
    if (hOutput == NULL)
        return eos_ERROR_PARAM_NULL;

    PService service = (PService) hService;

    unsigned i;
    for (i = 0; i < service->maxOutputs; i++) {
        POutput output = &service->outputs[i];
        if (!output->active) {
            output->active = TRUE;
            output->channel = params->channel;
            output->position = params->position;
            output->inverted = params->inverted;

            portInitialize(output);

            *hOutput = (eosHandle) output;
            break;
        }
    }
    if (i == service->maxOutputs)
        return eos_ERROR_OPERATION;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix una entrada
 *
 *       Funcio:
 *           eosResult eosOutputsDestroy(eosHandle hOutput)
 *
 *       Entrada:
 *           hOutput    : Handler de la sortida
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosOutputsDestroy(eosHandle hOutput) {

    if (hOutput == NULL)
        return eos_ERROR_PARAM_NULL;

    POutput output = (POutput) hOutput;
    output->active = FALSE;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           BOOL eosOutputsGet(eosHandle hInput)
 *
 *       Entrada:
 *           hInput     : handler de l'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

BOOL eosOutputsGet(eosHandle hInput) {

    if (hInput == NULL)
        return FALSE;

    return portGet((POutput) hInput);
}


/*************************************************************************
 *
 *       Inicialitza el port de sortida
 *
 *       Funcio:
 *           void portInitialize(POutput output)
 *
 *       Entrada:
 *           output     : Dades de l'entrada
 *
 *************************************************************************/

static void portInitialize(POutput output) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, output->channel, output->position, FALSE);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, output->channel, output->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port d'entrada
 *
 *       Funcio:
 *           BOOL portGet(POutput output)
 *
 *       Entrada:
 *           output     : Dates de la sortida
 *
 *       Retorn:
 *           Estat de la entrada
 *
 **************************************************************************/

static BOOL portGet(POutput output) {

    BOOL p = PLIB_PORTS_PinGetLatched(PORTS_ID_0, output->channel, output->position);
    return output->inverted ? !p : p;
}


/*************************************************************************
 *
 *       Asigna l'estat del port d'entrada
 *
 *       Funcio:
 *           void portSet(POutput output, BOOL state)
 *
 *       Entrada:
 *           output     : Dates de la sortida
 *           state      : L'estat a asignar
 *
 *       Retorn:
 *           Estat de la entrada
 *
 **************************************************************************/

static void portSet(POutput output, BOOL state) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, output->channel, output->position,
        output->inverted ? !state : state);
}
