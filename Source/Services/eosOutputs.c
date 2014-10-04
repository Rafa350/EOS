#include "Services/eosOutputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"
#include "System/eosQueue.h"


typedef struct {             // Dates d'una entrada
    BOOL active;             // -Indica si esta actiu
    PORTS_CHANNEL channel;   // -Canal del port
    PORTS_BIT_POS position;  // -Pin del port
    BOOL inverted;           // -Senyal invertida;
    unsigned time;           // -Temps restant del puls
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
    eosHandle hAttach;       // -Handler del servei TICK
} Service, *PService;


static void portInitialize(POutput output);
static BOOL portGet(POutput output);
static void portSet(POutput output, BOOL state);
static void portToggle(POutput output);


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
#ifdef eos_OPTION_CheckInputParams
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    // Crea les estructures de dades en el HEAP
    //
    PService service = eosAlloc(sizeof(Service) + (sizeof(Output) * params->maxOutputs));
    if (service == NULL)
        return eos_ERROR_ALLOC;

    // Inicialitza les estructures de dades
    //
    service->state = serviceStateInitialize;
    service->maxOutputs = params->maxOutputs;
    service->terminate = FALSE;
    service->outputs = (POutput)((BYTE*) service + sizeof(Service));

    unsigned i;
    for (i = 0; i < service->maxOutputs; i++)
        service->outputs[i].active = FALSE;

    // Asigna la funcio d'interrupcio TICK
    //
    eosHandle hTickService = params->hTickService;
    if (hTickService == NULL)
        hTickService = eosGetTickServiceHandle();
    if (hTickService != NULL)
        eosTickAttach(hTickService, eosOutputsISRTick, (eosHandle) service, &service->hAttach);
    else
        service->hAttach = NULL;

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
#ifdef eos_OPTION_CheckInputParams
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    PService service = (PService) hService;

    // Notifica el final i espera que finalitzi
    //
    service->terminate = TRUE;
    while (service->state != serviceStateTerminate)
        eosTimerTask(hService);

    if (service->hAttach)
        eosTickDeattach(service->hAttach);

    // Allibera la memoria de les estructures de dades
    //
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

#ifdef eos_OPTION_CheckInputParams
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    PService service = (PService) hService;

    switch (service->state) {
        case serviceStateInitialize:
            service->state = serviceStateActive;
            break;

        case serviceStateActive:
            if (service->terminate)
                service->state = serviceStateTerminate;
            break;

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

#ifdef eos_OPTION_CheckInputParams
    if (context == NULL)
        return;
#endif

    PService service = (PService) context;
    if (service->state == serviceStateActive) {
        unsigned i;
        for (i = 0; i < service->maxOutputs; i++) {
            POutput output = &service->outputs[i];
            if (output->active && output->time) {
                output->time -= 1;
                if (!output->time)
                    portToggle(output);
            }
        }
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

#ifdef eos_OPTION_CheckInputParams
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
    if (hOutput == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    PService service = (PService) hService;

    unsigned i;
    for (i = 0; i < service->maxOutputs; i++) {
        POutput output = &service->outputs[i];
        if (!output->active) {
            output->channel = params->channel;
            output->position = params->position;
            output->inverted = params->inverted;
            output->time = 0;

            portInitialize(output);

            *hOutput = (eosHandle) output;

            // Activar al final per evitar tenir que
            // desactivar les interrupcions
            //
            output->active = TRUE;

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

#ifdef eos_OPTION_CheckInputParams
    if (hOutput == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    POutput output = (POutput) hOutput;
    output->active = FALSE;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           BOOL eosOutputsGet(eosHandle hOutput)
 *
 *       Entrada:
 *           hOutput    : Handler de la sortida
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

BOOL eosOutputsGet(eosHandle hOutput) {

#ifdef eos_OPTION_CheckInputParams
    if (hOutput == NULL)
        return FALSE;
#endif

    return portGet((POutput) hOutput);
}


void eosOutputsSet(eosHandle hOutput, BOOL state) {

#ifdef eos_OPTION_CheckInputParams
    if (hOutput == NULL)
        return;
#endif

    portSet((POutput) hOutput, state);
}


void eosOutputsToggle(eosHandle hOutput) {

#ifdef eos_OPTION_CheckInputParams
    if (hOutput == NULL)
        return;
#endif

    portToggle((POutput) hOutput);
}


void eosOutputsPulse(eosHandle hOutput, unsigned time) {

#ifdef eos_OPTION_CheckInputParams
    if (hOutput == NULL)
        return;
#endif

    POutput output = (POutput) hOutput;

    BOOL intFlag = eosGetInterruptState();
    eosDisableInterrupts();
    if (!output->time)
        portToggle(output);
    output->time = time;
    if (intFlag)
        eosEnableInterrupts();
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
 **************************************************************************/

static void portSet(POutput output, BOOL state) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, output->channel, output->position,
        output->inverted ? !state : state);
}


/*************************************************************************
 *
 *       Canvia l'estat del port d'entrada
 *
 *       Funcio:
 *           void portToggle(POutput output)
 *
 *       Entrada:
 *           output     : Dates de la sortida
 *
 **************************************************************************/

static void portToggle(POutput output) {

    PLIB_PORTS_PinToggle(PORTS_ID_0, output->channel, output->position);
}
