#include "Services/eosForms.h"
#include "System/eosQueue.h"
#include "System/eosMemory.h"


typedef enum {
    serviceInitializing,
    serviceRunning
} ServiceStates;

typedef struct __eosForm {
    eosCallback onMessage;
    eosHForm hNextForm;
    void *privateData;
} eosForm;

typedef struct __eosFormsService {
    ServiceStates state;
    eosHQueue hQueue;
    eosForm hActiveForm;
    eosHForm hFirstForm;
} eosFormsService;


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosHFormsService eosFormsServiceInitialize(
 *               eosFormsServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del servei
 *
 *************************************************************************/

eosHFormsService eosFormsServiceInitialize(
    eosFormsServiceParams *params) {

    eosHFormsService hService = eosAlloc(sizeof(eosFormsService));
    if (hService == NULL)
        return NULL;

    hService->state = serviceInitializing;
    hService->hFirstForm = NULL;
    hService->hActiveForm = NULL;

    eosQueueParams queueParams;
    queueParams.itemSize = sizeof(eosFormsMessage);
    queueParams.maxItems = 50;
    hService->hQueue = eosQueueCreate(&queueParams);
    
    return hService;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosFormsServiceTask(
 *               eosHFormsService hService)
 *
 *       Entrada:
 *           hService: Handler del servei
 *
 *************************************************************************/

void eosFormsServiceTask(
    eosHFormsService hService) {

    switch (hService->state) {
        case serviceInitializing:
            hService->state = serviceRunning;
            break;

        case serviceRunning: {

            eosFormsMessage message;

            while (eosFormsGetMessage(hService, &message)) {
                eosHForm hForm = hService->hActiveForm;
                if (hForm != NULL) {
                    if (hForm->onMessage != NULL)
                        hForm->onMessage(hForm, &message);
                }
            }
            break;
        }
    }
}


/*************************************************************************
 *
 *
 *       Funcio:
 *
 *       Entrada:
 *
 *       Retorn:
 *
 *
 *************************************************************************/

void eosFormsSendMessage(
    eosHFormsService hService,
    eosFormsMessage *message) {

    eosQueuePut(hService->hQueue, message);
}


/*************************************************************************
 *
 *
 *       Funcio:
 *
 *       Entrada:
 *
 *       Retorn:
 *
 *
 *************************************************************************/

bool eosFormsGetMessage(
    eosHFormsService hService,
    eosFormsMessage *message) {

    return eosQueueGet(hService->hQueue, message);
}
