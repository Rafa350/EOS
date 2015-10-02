#include "eos.h"

#if eosOPTIONS_UseDigInputService == 1

#include "Services/eosDigInput.h"
#include "System/eosMemory.h"
#include "System/eosTask.h"

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"


#define PATTERN_ON       0x0000007F
#define PATTERN_OFF      0x00000080
#define PATTERN_MASK     0x000000FF


typedef struct __eosDigInput {         // Dades d'una entrada
    eosDigInputServiceHandle hService; // -El servei al que pertany
    eosDigInputHandle hNextInput;      // -Seguent element
    eosDigPinID pin;                   // -Identificador del pin
    bool inverted;                     // -Senyal invertida
    eosDigInputCallback onPosEdge;     // -Event POSEDGE
    eosDigInputCallback onNegEdge;     // -Event NEGEDGE
    eosDigInputCallback onChange;      // -Event CHANGE
    bool onPosEdgeFired;
    bool onNegEdgeFired;
    bool onChangeFired;
    void *context;                     // -Parametre del event
    uint32_t pattern;                  // -Patro de filtratge
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
    
    eosDebugVerify(params != NULL);

    eosDigInputServiceHandle hService = eosAlloc(sizeof(eosDigInputService));
    if (hService != NULL) {
        hService->hFirstInput = NULL;
        hService->hTask = eosTaskCreate(tskIDLE_PRIORITY + params->priority, 
                512, task, hService);
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
        hInput->pin = params->pin;
        hInput->inverted = params->inverted;
        hInput->onPosEdge = params->onPosEdge;
        hInput->onNegEdge = params->onNegEdge;
        hInput->onChange = params->onChange;
        hInput->onPosEdgeFired = false;
        hInput->onNegEdgeFired = false;
        hInput->onChangeFired = false;

        eosCriticalSectionInfo csInfo;
        eosEnterCriticalSection(eosCriticalSectionSeverityLow, &csInfo);

        hInput->hNextInput = hService->hFirstInput;
        hService->hFirstInput = hInput;

        eosLeaveCriticalSection(&csInfo);

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

    eosCriticalSectionInfo csInfo;
    eosEnterCriticalSection(eosCriticalSectionSeverityLow, &csInfo);
    
    bool result = hInput->posEdge;
    hInput->posEdge = false;

    eosLeaveCriticalSection(&csInfo);

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

    eosCriticalSectionInfo csInfo;
    eosEnterCriticalSection(eosCriticalSectionSeverityLow, &csInfo);

    bool result = hInput->negEdge;
    hInput->negEdge = false;

    eosLeaveCriticalSection(&csInfo);

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

    unsigned tc = eosGetTickCount();
    eosDigInputServiceHandle hService = params;

    while (true) {
        
        eosTaskDelayUntil(10, &tc);
        
        eosDigInputHandle hInput, hFirstInput;
        eosCriticalSectionInfo csInfo;
        
        // Explora les entrades per coneixa el seu estat
        //
        eosEnterCriticalSection(eosCriticalSectionSeverityLow, &csInfo);
        
        hFirstInput = hService->hFirstInput;
        
        hInput = hFirstInput;
        while (hInput) {

            hInput->pattern <<= 1;
            if (portGet(hInput))
                hInput->pattern |= 1;

            if ((hInput->pattern & PATTERN_MASK) == PATTERN_ON) {
                hInput->state = true;
                hInput->posEdge = true;
                if (hInput->onPosEdge != NULL) 
                    hInput->onPosEdgeFired = true;
                else if (hInput->onChange != NULL) 
                    hInput->onChangeFired = true;
            }
            else if ((hInput->pattern & PATTERN_MASK) == PATTERN_OFF) {
                hInput->state = false;
                hInput->negEdge = true;
                if (hInput->onNegEdge != NULL) 
                    hInput->onNegEdgeFired = true;
                else if (hInput->onChange != NULL) 
                    hInput->onChangeFired = true;
            }

            hInput = hInput->hNextInput;
        }
        
        eosLeaveCriticalSection(&csInfo);
        
        // Crida a les funcions callback corresponents
        //
        hInput = hFirstInput;
        while (hInput) {
            
            if (hInput->onPosEdgeFired) 
                hInput->onPosEdge(hInput, hInput->context);
            else if (hInput->onNegEdgeFired) 
                hInput->onNegEdge(hInput, hInput->context);
            else if (hInput->onChangeFired) 
                hInput->onChange(hInput, hInput->context);
            
            hInput = hInput->hNextInput;
        }
        
        // Reseteja flags i variables temporals
        //
        eosEnterCriticalSection(eosCriticalSectionSeverityLow, &csInfo);

        hInput = hFirstInput;
        while (hInput) {
            
            if (hInput->onPosEdgeFired) {
                hInput->onPosEdgeFired = false;
                hInput->posEdge = false;
            }
            if (hInput->onNegEdgeFired) {
                hInput->onNegEdgeFired = false;
                hInput->negEdge = false;
            }
            if (hInput->onChangeFired) {
                hInput->onChangeFired = false;
                hInput->posEdge = false;
            }           
            
            hInput = hInput->hNextInput;
        }

        eosLeaveCriticalSection(&csInfo);
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
    eosDigPinInputMode(hInput->pin);
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
    
    bool p = eosDigPinGet(hInput->pin);
    return hInput->inverted ? !p : p;
}


#endif
