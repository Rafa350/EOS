#include "eos.h"
#include "System/eosTask.h"
#include "System/eosMemory.h"
#include "Services/eosAppLoop.h"


typedef struct __eosAppLoopService {    
    eosTaskHandle hTask;
} eosAppLoopService;


extern void appSetup(void);
extern void appLoop(void);


static void task(void *params);


/*************************************************************************
 *
 *       Inicialitzacio el servei de gestio de l'aplicacio d'usuari
 *
 *       Funcio:
 *           eosAppLoopServiceHandle eosAppLoopServiceInitialize(
 *               eosAppLoopServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio del servei
 *
 *       Retorn:
 *           El handler del servei. NULL en cas d'error
 *
 *************************************************************************/

eosAppLoopServiceHandle eosAppLoopServiceInitialize(
    eosAppLoopServiceParams *params) {
    
    eosDebugVerify(params != NULL);
    
    eosAppLoopServiceHandle hService = eosAlloc(sizeof(eosAppLoopService));
    if (hService != NULL) {
        
        hService->hTask = eosTaskCreate(params->appPriority, params->appStackSize, task, hService);
        eosDebugVerify(hService->hTask != NULL);
    }
    
    return hService;
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

static void task(
    void *params) {
    
    //eosAppLoopServiceHandle hService = params;
    
    appSetup();
    while (true)
        appLoop();
}
