#define __EOS_INPUTS_INTERNAL
#include "Services/eosInputs.h"
#include "Services/eosTick.h"
#include "System/eosMemory.h"


// Estats del servei
//
#define SS_INITIALIZING           0    // Inicialitzant
#define SS_RUNNING                1    // En execucio

#define PATTERN_ON       0x00007FFF
#define PATTERN_OFF      0x00008000
#define PATTERN_MASK     0x0000FFFF


struct __eosInput {                    // Dades d'una entrada
    struct __eosInputService *service; // -El servei al que pertany
    struct __eosInput *nextInput;      // -Seguent entrada
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
};

struct __eosInputService {             // Dades del servei
    unsigned state;                    // -Estat del servei
    struct __eosInput *firstInput;     // -Primera entrada de la llista
};


static void portInitialize(eosInput input);
static BOOL portGet(eosInput input);


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosResult eosInputServiceInitialize(
 *               eosInputServiceParams *params,
 *               eosInputService *service)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Sortida:
 *           service: El handler del servei
 *
 *       Retorn:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosInputServiceInitialize(eosInputServiceParams *params, eosInputService *_service) {

    eosInputService service = eosAlloc(sizeof(struct __eosInputService));
    if (service == NULL)
        return eos_ERROR_ALLOC;

    service->state = SS_INITIALIZING;
    service->firstInput = NULL;

    // Asigna la funcio d'interrupcio TICK
    //
    eosTickService tickService = params->tickService;
    if (tickService == NULL)
        tickService = eosGetTickServiceHandle();
    if (tickService != NULL)
        eosTickAttach(tickService, (eosCallback) eosInputServiceISRTick, service);

    *_service = service;
   
    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosInputServiceTask(
 *               eosInputService service)
 * 
 *       Entrada:
 *           service: El handler servei
 *
 *************************************************************************/

void eosInputServiceTask(eosInputService service) {

    switch (service->state) {
        case SS_INITIALIZING:
            service->state = SS_RUNNING;
            break;

        case SS_RUNNING: {

            eosInput input = service->firstInput;
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
 *               eosInputService service)
 *
 *       Entrada:
 *           service: El handler servei
 *
 *************************************************************************/

void eosInputServiceISRTick(eosInputService service) {

    if (service->state == SS_RUNNING) {
        
        eosInput input = service->firstInput;
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
 *           eosResult eosInputCreate(
 *               eosInputService service,
 *               eosInputParams* params,
 *               eosInput *input)
 *
 *       Entrada:
 *           service: El servei
 *           params : Parametres de la entrada
 *
 *       Sortida:
 *           input: El handler de la entrada
 *
 *       Retorn:
 *           El resultat de l'operacio
 *
 *************************************************************************/

eosResult eosInputCreate(eosInputService service, eosInputParams* params, eosInput *_input) {

    eosInput input = eosAlloc(sizeof(struct __eosInput));
    if (input == NULL)
        return eos_ERROR_ALLOC;

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

    *_input = input;

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix una entrada
 *
 *       Funcio:
 *           eosResult eosInputDestroy(
 *               eosInput input)
 *
 *       Entrada:
 *          input: El handler de l'entrada
 *
 *************************************************************************/

eosResult eosInputDestroy(eosInput input) {

    return eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           BOOL eosInputGet(
 *               eosInput input)
 *
 *       Entrada:
 *           input: El handler de l'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

BOOL eosInputGet(eosInput input) {

    return input->state;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           BOOL eosInputPosEdge(
 *               eosInput input)
 *
 *       Entrada:
 *           input: El handler de l'entrada
 *
 *       Retorn:
 *           TRUS si s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputPosEdge(eosInput input) {

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
 *               eosInput input)
 *
 *       Entrada:
 *           input: L'entrada
 *
 *       Retorn:
 *           TRUS si s'ha produit el flanc
 *
 *************************************************************************/

BOOL eosInputNegEdge(eosInput input) {

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
 *               eosInput input)
 *
 *       Entrada:
 *           input: El handler de l'entrada
 *
 *************************************************************************/

static void portInitialize(eosInput input) {

    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, input->channel, input->position);
}


/*************************************************************************
 *
 *       Obte l'estat del port d'entrada
 *
 *       Funcio:
 *           BOOL portGet(
 *               eosInput input)
 *
 *       Entrada:
 *           input: El handler de l'entrada
 *
 *       Retorn:
 *           Estat de la entrada
 *
 **************************************************************************/

static BOOL portGet(eosInput input) {

    BOOL p = PLIB_PORTS_PinGet(PORTS_ID_0, input->channel, input->position);
    return input->inverted ? !p : p;
}
