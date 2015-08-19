#include "eos.h"

#if eosOPTIONS_UseDigOutputService == 1

#include "Services/eosDigOutput.h"
#include "System/eosMemory.h"
#include "System/eosTask.h"
#include "peripheral/ports/plib_ports.h"


#define TASK_PERIOD 10


typedef struct __eosDigOutput {        // Dades d'una sortida
    PORTS_CHANNEL channel;             // -Canal
    PORTS_BIT_POS position;            // -Posicio
    bool inverted;                     // -Senyal invertida
    unsigned timeout;                  // -Contador de temps
    eosDigOutputServiceHandle hService;// -El servei al que pertany
    eosDigOutputHandle hNextOutput;    // -Seguent sortida
} eosDigOutput;

typedef struct __eosDigOutputService { // Dades del servei
    eosDigOutputHandle hFirstOutput;   // -Primera sortida
    eosTaskHandle hTask;               // -Tasca del servei
} eosDigOutputService;


static void task(void *params);
static void portInitialize(eosDigOutputHandle hOutput);
static bool portGet(eosDigOutputHandle hOutput);
static void portSet(eosDigOutputHandle hOutput, bool state);
static void portToggle(eosDigOutputHandle hOutput);


/*************************************************************************
 *
 *       Inicialitzacio el servei de gestio de sortides
 *
 *       Funcio:
 *           eosDigOutputServiceHandle eosDigOutputServiceInitialize(
 *               eosOutputServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 *
 *************************************************************************/

eosDigOutputServiceHandle eosDigOutputServiceInitialize(
    eosDigOutputServiceParams *params) {

    eosDigOutputServiceHandle hService = eosAlloc(sizeof(eosDigOutputService));
    if (hService != NULL) {
        hService->hFirstOutput = NULL;
        hService->hTask = eosTaskCreate(0, 512, task, hService);
    }
    
    return hService;
}


/*************************************************************************
 *
 *       Crea una sortida
 *
 *       Funcio:
 *           eosDigOutputHandle eosDigOutputsCreate(
 *               eosDigOutputServiceHandle hService,
 *               eosOutputParams *params)
 *
 *       Entrada:
 *           hService: El handler del servei
 *           params  : Parametres d'inicialitzacio de la sortida
 *
 *       Retorn:
 *           El handler de la sortida. NULL en cas d'error
 *
 *************************************************************************/

eosDigOutputHandle eosDigOutputCreate(
    eosDigOutputServiceHandle hService,
    eosDigOutputParams *params) {

    eosDebugVerify(hService != NULL);
    eosDebugVerify(params != NULL);

    // Crea el bloc de memoria
    //
    eosDigOutputHandle hOutput = eosAlloc(sizeof(eosDigOutput));
    if (hOutput != NULL) {

        // Inicialitza les dades internes de la sortida
        //
        hOutput->hService = hService;   
        hOutput->channel = params->channel;
        hOutput->position = params->position;
        hOutput->inverted = params->inverted;
        hOutput->timeout = 0;

        // Afegeis la sortida a la llista de sortides del servei
        //
        eosTaskSuspendAll();
        hOutput->hNextOutput = hService->hFirstOutput;
        hService->hFirstOutput = hOutput;
        eosTaskResumeAll();

        // Inicialitza el port fisic a estat OFF
        //
        portInitialize(hOutput);
    }
    
    return hOutput;
}


/*************************************************************************
 *
 *       Obte l'estat d'una sortida
 *
 *       Funcio:
 *           bool eosDigOutputsGet(
 *               eosDigOutputHandle hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *       Retorn:
 *           L'estat de la sortida
 *
 *************************************************************************/

bool eosDigOutputGet(
    eosDigOutputHandle hOutput) {
    
    eosDebugVerify(hOutput != NULL);

    return portGet(hOutput);
}


/*************************************************************************
 *
 *       Assigna l'estat d'una sortida
 *
 *       Funcio:
 *           void eosDigOutputsSet(
 *               eosDigOutputHandle hOutput,
 *               bool state)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *           state  : L'estat a signar
 *
 *************************************************************************/

void eosDigOutputSet(
    eosDigOutputHandle hOutput,
    bool state) {

    eosDebugVerify(hOutput != NULL);

    eosTaskSuspendAll();
    
    portSet(hOutput, state);
    hOutput->timeout = 0;
    
    eosTaskResumeAll();
}


/*************************************************************************
 *
 *       Inverteix l'estat d'una sortida
 *
 *       Funcio:
 *           void eosDigOutputToggle(
 *               eosDigOutput hOutput)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *
 *************************************************************************/

void eosDigOutputToggle(
    eosDigOutputHandle hOutput) {

    eosDebugVerify(hOutput != NULL);

    eosTaskSuspendAll();
    
    portToggle(hOutput);
    hOutput->timeout = 0;
    
    eosTaskResumeAll();
}


/*************************************************************************
 *
 *       Genera un puls d'inversio de l'estat d'una sortida. La resolucio
 *       es en multiples de TASK_PERIOD
 *
 *       Funcio:
 *           void eosDigOutputPulse(
 *               eosDigOutput hOutput,
 *               unsigned time)
 *
 *       Entrada:
 *           hOutput: El handler de la sortida
 *           time   : Duracio del puls
 * 
 *       Notes:
 *           Si encara esta en un puls, unicament l'allarga
 *
 *************************************************************************/

void eosDigOutputPulse(
    eosDigOutputHandle hOutput,
    unsigned time) {

    eosDebugVerify(hOutput != NULL);

    if (time >= TASK_PERIOD) {

        eosTaskSuspendAll();
        
        if (hOutput->timeout == 0)
            portToggle(hOutput);
        hOutput->timeout = time / TASK_PERIOD;
        
        eosTaskResumeAll();
    }
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void task(
 *               void *param)
 *
 *       Entrada:
 *           param : Parametre (hService)
 *
 *************************************************************************/

static void task(void *param) {

    unsigned tc = eosTaskGetTickCount();
    eosDigOutputServiceHandle hService = param;

    while (true) {

        eosTaskDelayUntil(TASK_PERIOD, &tc);
        
        eosTaskSuspendAll();
        
        eosDigOutputHandle hOutput = hService->hFirstOutput;
        while (hOutput != NULL) {
            
            unsigned timeout = hOutput->timeout;
            if (timeout > 0) {
                timeout -= 1;
                if (timeout == 0)
                    portToggle(hOutput);
                hOutput->timeout = timeout;
            }        
            hOutput = hOutput->hNextOutput;
        }
        
        eosTaskResumeAll();
    }
}


static void portInitialize(
    eosDigOutputHandle hOutput) {
        
    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position, hOutput->inverted ? true : false);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, hOutput->channel, hOutput->position);
}


static bool portGet(
    eosDigOutputHandle hOutput) {
    
    bool p = PLIB_PORTS_PinGet(PORTS_ID_0, hOutput->channel, hOutput->position);
    return hOutput->inverted ? !p : p;
}


static void portSet(
    eosDigOutputHandle hOutput, 
    bool state) {
    
    PLIB_PORTS_PinWrite(PORTS_ID_0, hOutput->channel, hOutput->position, 
        hOutput->inverted ? state : !state);
}


static void portToggle(
    eosDigOutputHandle hOutput) {

    PLIB_PORTS_PinToggle(PORTS_ID_0, hOutput->channel, hOutput->position);    
}


#endif
