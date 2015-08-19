#include "eos.h"

#if eosOPTIONS_UseDigInputService == 1

#include "Services/eosDigInput.h"
#include "System/eosMemory.h"
#include "System/eosTask.h"
#include "peripheral/ports/plib_ports.h"


#define PATTERN_ON       0x0000007F
#define PATTERN_OFF      0x00000080
#define PATTERN_MASK     0x000000FF


typedef struct __eosDigInput {         // Dades d'una entrada
    eosDigInputServiceHandle hService; // -El servei al que pertany
    eosDigInputHandle hNextInput;      // -Seguent element
    PORTS_CHANNEL channel;             // -Canal
    PORTS_BIT_POS position;            // -Posicio
    bool inverted;                     // -Senyal invertida
    eosDigInputCallback onPosEdge;     // -Event POSEDGE
    eosDigInputCallback onNegEdge;     // -Event NEGEDGE
    eosDigInputCallback onChange;      // -Event CHANGE
    void *context;                     // -Parametre del event
    UINT32 pattern;                    // -Patro de filtratge
    bool state;                        // -Indicador ON/OFF
    bool posEdge;                      // -Indica si s'ha rebut un flanc positiu
    bool negEdge;                      // -Indica si s'ha rebut un flanc negatiu
} eosDigInput;

typedef struct __eosDigInputService {  // Dades del servei
    eosDigInputHandle hFirstInput;     // -Primer element de la llista
    eosTaskHandle hTask;               // -Tasca del servei
} eosDigInputService;


static void task(void *params);
static void portInitialize(eosDigInputHandle hInput);
static bool portGet(eosDigInputHandle hInput);


/*************************************************************************
 *
 *       Inicialitzacio el servei
 *
 *       Funcio:
 *           eosDigInputServiceHandle eosDigInputServiceInitialize(
 *               eosDigInputServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 *
 *************************************************************************/

eosDigInputServiceHandle eosDigInputServiceInitialize(
    eosDigInputServiceParams *params) {

    eosDigInputServiceHandle hService = eosAlloc(sizeof(eosDigInputService));
    if (hService != NULL) {
        hService->hFirstInput = NULL;
        hService->hTask = eosTaskCreate(0, 512, task, hService);
   }

    return hService;
}


/*************************************************************************
 *
 *       Crea una entrada
 *
 *       Funcio:
 *           eosDigInputHandle eosDigInputCreate(
 *               eosDigInoputServiceHandle hService,
 *               eosDigInputParams *params)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           params  : Parametres de la entrada
 *
 *       Retorn:
 *           El handler de la entrada
 *
 *************************************************************************/

eosDigInputHandle eosDigInputCreate(
    eosDigInputServiceHandle hService,
    eosDigInputParams *params) {
    
    eosDebugVerify(hService != NULL);
    eosDebugVerify(params != NULL);

    eosDigInputHandle hInput = eosAlloc(sizeof(eosDigInput));
    if (hInput != NULL) {

        hInput->hService = hService;
        hInput->posEdge = false;
        hInput->negEdge = false;
        hInput->channel = params->channel;
        hInput->position = params->position;
        hInput->inverted = params->inverted;
        hInput->onPosEdge = params->onPosEdge;
        hInput->onNegEdge = params->onNegEdge;
        hInput->onChange = params->onChange;

        eosTaskSuspendAll();
        hInput->hNextInput = hService->hFirstInput;
        hService->hFirstInput = hInput;
        eosTaskResumeAll();

        portInitialize(hInput);
        hInput->state = portGet(hInput);
        if (hInput->state)
            hInput->pattern = 0xFFFFFFFF;
        else
            hInput->pattern = 0x00000000;
    }
    
    return hInput;
}


/*************************************************************************
 *
 *       Obte l'estat de l'entrada
 *
 *       Funcio:
 *           bool eosDigInputGet(
 *               eosDigInputHandle hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           L'estat de l'entrada
 *
 *************************************************************************/

bool eosDigInputGet(
    eosDigInputHandle hInput) {
    
    eosDebugVerify(hInput != NULL);

    return hInput->state;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc ascendent (OFF->ON)
 *
 *       Funcio:
 *           bool eosDigInputPosEdge(
 *               eosDigInputHandle hInput)
 *
 *       Entrada:
 *           hInput: El handler de l'entrada
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool eosDigInputPosEdge(
    eosDigInputHandle hInput) {

    eosDebugVerify(hInput != NULL);

    eosTaskSuspendAll();
    bool result = hInput->posEdge;
    hInput->posEdge = false;
    eosTaskResumeAll();
    return result;
}


/*************************************************************************
 *
 *       Comprova si s'ha produit un flanc descendent (ON->OFF)
 *
 *       Funcio:
 *           bool eosDigInputNegEdge(
 *               eosDigInputHandle hInput)
 *
 *       Entrada:
 *           hInput: L'entrada
 *
 *       Retorn:
 *           True si s'ha produit el flanc
 *
 *************************************************************************/

bool eosDigInputNegEdge(
    eosDigInputHandle hInput) {

    eosDebugVerify(hInput != NULL);

    eosTaskSuspendAll();
    bool result = hInput->negEdge;
    hInput->negEdge = false;
    eosTaskResumeAll();
    return result;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void task(void *params)
 *
 *       Entrada:
 *           params: Parametres de la funcio (hService)
 *
 *************************************************************************/

static void task(
    void *params) {

    unsigned tc = eosTaskGetTickCount();
    eosDigInputServiceHandle hService = params;

    while (true) {
        
        eosTaskDelayUntil(10, &tc);
        
        eosDigInputHandle hInput;
        
        // Explora les entrades per coneixa el seu estat
        //
        hInput = hService->hFirstInput;
        while (hInput) {

            hInput->pattern <<= 1;
            if (portGet(hInput))
                hInput->pattern |= 1;

            if ((hInput->pattern & PATTERN_MASK) == PATTERN_ON) {
                hInput->state = true;
                hInput->posEdge = true;
                if (hInput->onPosEdge != NULL) {
                    hInput->onPosEdge(hInput, hInput->context);
                    hInput->posEdge = false;
                }
                else if (hInput->onChange != NULL) {
                    hInput->onChange(hInput, hInput->context);
                    hInput->posEdge = false;
                }
            }
            else if ((hInput->pattern & PATTERN_MASK) == PATTERN_OFF) {
                hInput->state = false;
                hInput->negEdge = true;
                if (hInput->onNegEdge != NULL) {
                    hInput->onNegEdge(hInput, hInput->context);
                    hInput->negEdge = false;
                }
                else if (hInput->onChange != NULL) {
                    hInput->onChange(hInput, hInput->context);
                    hInput->negEdge = false;
                }
            }

            hInput = hInput->hNextInput;
        }
        
        // Crida a les funcions callback corresponents
        //
        /*hInput = hService->hFirstInput;
        while (hInput) {

            hInput = hInput->hNextInput;
        }*/
        
        // Reseteja flags i variables temporals
        //
        /*
        eosTaskSuspendAll();
        hInput = hService->hFirstInput;
        while (hInput) {

            hInput = hInput->hNextInput;
        }
        eosTaskResumeAll();*/
    }
}


/*************************************************************************
 *
 *       Inicialitza el port d'una entrada
 *
 *       Funcio:
 *           void portInitialize(
 *               eosDigInputHandle hInput) 
 * 
 *       Entrada:
 *           hInput: Hander de la entrada
 *
 *************************************************************************/

static void portInitialize(
    eosDigInputHandle hInput) {
       
    /*if (PLIB_PORTS_ExistsPinMode(PORTS_ID_0))
        PLIB_PORTS_PinModeSelect(PORTS_ID_0, PORTS_ANALOG_PIN_0, PORTS_PIN_MODE_DIGITAL);
    else if (PLIB_PORTS_ExistsPinModePerPort(PORTS_ID_0))
        PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, hInput->channel, hInput->position, PORTS_PIN_MODE_DIGITAL);
    
    if (PLIB_PORTS_ExistsChangeNoticePullUp(PORTS_ID_0))
        PLIB_PORTS_ChangeNoticePullUpEnable(PORTS_ID_0, 0);
    else if (PLIB_PORTS_ExistsChangeNoticePullUpPerPort(PORTS_ID_0))
        PLIB_PORTS_ChangeNoticePullUpPerPortEnable(PORTS_ID_0, hInput->channel, hInput->position);
    */
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, hInput->channel, hInput->position);
}


/*************************************************************************
 *
 *       Lectura del port d'una entrada
 *
 *       Funcio:
 *           bool portGet(
 *               eosDigInputHandle hInput) 
 * 
 *       Entrada:
 *           hInput: Handler de l'entrada
 * 
 *       Retorn:
 *           Valor lleigit del port
 *
 *************************************************************************/

static bool portGet(
    eosDigInputHandle hInput) {
    
    bool p = PLIB_PORTS_PinGet(PORTS_ID_0, hInput->channel, hInput->position);
    return hInput->inverted ? !p : p;
}


#endif
