#include "Services/eosInputs.h"
#include "System/eosMemory.h"


#define PATTERN_ON           0x00007FFF
#define PATTERN_OFF          0x00008000
#define PATTERN_MASK         0x0000FFFF


typedef struct {             // Dates d'una entrada
    unsigned pattern;        // -Patro de filtratge
    unsigned active:1;       // -Indica si esta lliure
    unsigned state:1;        // -Indica l'estat de la entrada (ON/OFF)
    unsigned posEdge:1;      // -Indica si s'ha detectat un flanc positiu
    unsigned negEdge:1;      // -Indica si s'ha detectat un flanc negatiu
} Input, *PInput;

typedef enum {                    // Estat del servei
    SS_INITIALIZE,                // -Inicialitza
    SS_TERMINATE,                 // -Finalitza
    SS_ACTIVE,                    // -Actiu
} ServiceState;

typedef struct {             // Dades del servei
    ServiceState state;      // -Estat del servei
    unsigned triggered;      // -Indica event del temporitzador
    unsigned maxInputs;      // -Numero maxim d'entrades a gestionar
    PInput inputs;           // -Llista d'entrades
    BOOL terminate;          // -Indica si cal finalitzar el servei
} Service, *PService;


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosResult eosInputsInitialize(
 *               unsigned maxInputs,
 *               eosHandle *hService)
 *
 *       Entrada:
 *           maxInputs  : Numero maxim d'entrades a gestionar
 *
 *       Sortida:
 *           hService   : El handler del servei
 *
 *       Retorn:
 *           eos_RETURN_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosInputsInitialize(unsigned maxInputs, eosHandle *hService) {

    // Comprova els parametres
    //
    if (hService == NULL)
        return eos_ERROR_PARAM_NULL;

    // Crea les estrucxtures de dades en el HEAP
    //
    PService service = eosAlloc(sizeof(Service));
    if (service == NULL)
        return eos_ERROR_ALLOC;

    PInput inputs = eosAlloc(sizeof(Input) * maxInputs);
    if (inputs == NULL) {
        eosFree(service);
        return eos_ERROR_ALLOC;
    }

    // Inicialitza les estructures de dades
    //
    service->state = SS_INITIALIZE;
    service->maxInputs = maxInputs;
    service->inputs = inputs;
    service->terminate = FALSE;

    unsigned i;
    for (i = 0; i < maxInputs; i++)
        service->inputs[i].active = 0;

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
    while (service->state != SS_TERMINATE)
        eosTimerTask(hService);

    // Allibera la memoria de les estructures de dades
    //
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
        case SS_INITIALIZE:
            service->state = SS_ACTIVE;
            break;

        case SS_ACTIVE: {

            BOOL intFlag = eosGetInterruptState();
            eosDisableInterrupts();
            unsigned triggered = service->triggered;
            service->triggered = 0;
            if (intFlag)
                eosEnableInterrupts();

            if (triggered) {
                unsigned i;
                for (i = 0; i < service->maxInputs; i++) {
                    PInput input = &service->inputs[i];
                    if (input->active == 1) {

                        // LLeigir entrada fisica
                        //
                        input->pattern = (input->pattern << 1) | 1;
                        if ((input->pattern & PATTERN_MASK) == PATTERN_ON) {
                            input->state = 1;
                            input->posEdge = 1;
                        }
                        else if ((input->pattern & PATTERN_MASK) == PATTERN_OFF) {
                            input->state = 0;
                            input->negEdge = 1;
                        }
                    }
                }
            }
            if (service->terminate)
                service->state = SS_TERMINATE;
            break;
        }

        case SS_TERMINATE:
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
    service->triggered += 1;
}
