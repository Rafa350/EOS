#include "Services/eosForms.h"
#include "System/eosQueue.h"
#include "System/eosMemory.h"


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -Procesate missatges
} ServiceStates;

typedef struct __eosForm {             // Dades del formulari
    eosHFormsService hService;         // -Handler del servei
    eosHForm hParent;                  // -Handler del form pare
    eosCallback onMessage;             // -Callback de cada missatge
    eosHForm hNextForm;                // -Seguent form de la llista
    void *privateData;                 // -Dades privades del formulari
} eosForm;

typedef struct __eosFormsService {     // Dades del servei
    ServiceStates state;               // -Estat del servei
    axHDisplayService hDisplayService; // -Servei de display
    eosCallback onMessage;             // -Calback en cada missatge
    eosHQueue hQueue;                  // -Cua de missatges
    eosHForm hActiveForm;              // -Formulari actiu
    eosHForm hFirstForm;               // -Primer formulari de la llista
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
    hService->hDisplayService = params->hDisplayService;
    hService->onMessage = params->onMessage;
    hService->hFirstForm = NULL;
    hService->hActiveForm = NULL;

    eosQueueParams queueParams;
    queueParams.itemSize = sizeof(eosFormsMessage);
    queueParams.maxItems = eosOPTIONS_FORMS_MAX_QUEUE_SIZE;
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
            if (axDisplayServiceIsInitialized(hService->hDisplayService))
                hService->state = serviceRunning;
            break;

        case serviceRunning: {

            eosFormsMessage message;

            while (eosFormsGetMessage(hService, &message)) {

                if (hService->onMessage != NULL)
                    hService->onMessage(hService, &message);

                if (message.id != MSG_NULL) {
                    eosHForm hForm = message.hForm;
                    if ((hForm != NULL) &&  (hForm->onMessage != NULL))
                        hForm->onMessage(hService, &message);
                }
            }
            break;
        }
    }
}


/*************************************************************************
 *
 *       Crea un form
 *
 *       Funcio:
 *           eosHForm eosFormsCreateForm(
 *               eosHFormsService hService,
 *               eosFormParams *params)
 *
 *       Entrada:
 *           hService: El handler del servei
 *           params  : Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del form, NULL en cas d'error
 *
 *************************************************************************/

eosHForm eosFormsCreateForm(
    eosHFormsService hService,
    eosFormParams *params) {

    eosHForm hForm = eosAlloc(sizeof(eosForm));
    if (hForm == NULL)
        return NULL;

    hForm->hParent = params->hParent;
    hForm->privateData = eosAlloc(params->privateDataSize);
    hForm->onMessage = params->onMessage;
    hForm->hNextForm = hService->hFirstForm;
    hForm->hService = hService;
    hService->hFirstForm = hForm;
    
    eosFormsMessage message;
    message.id = MSG_INITIALIZE;
    message.hForm = hForm;
    eosFormsSendMessage(hService, &message);

    return hForm;
}


/*************************************************************************
 *
 *       Obte el formulari actiu
 *
 *       Funcio:
 *           eosHForm eosFormsGetActiveForm(
 *               eosHFormsService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           El handler del formulari actiu
 *
 **************************************************************************/

eosHForm eosFormsGetActiveForm(
    eosHFormsService hService) {

    return hService->hActiveForm;
}


/*************************************************************************
 *
 *       Canvia el formulari actiu
 *
 *       Funcio:
 *           eosHForm eosFormsSetActiveForm(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm   : El formulari a activat
 *
 *       Retorn:
 *           El anterior formulari actiu
 *
 *************************************************************************/

eosHForm eosFormsSetActiveForm(
    eosHForm hForm) {
    
    eosFormsMessage message;

    eosHFormsService hService = hForm->hService;

    eosHForm hInactiveForm = hService->hActiveForm;
    if (hInactiveForm != NULL) {
        message.id = MSG_DEACTIVATE;
        message.hForm = hInactiveForm;
        eosFormsSendMessage(hService, &message);
    }
    
    hService->hActiveForm = hForm;

    if (hForm != NULL) {
        message.id = MSG_ACTIVATE;
        message.hForm = hForm;
        eosFormsSendMessage(hService, &message);
    }
    
    return hInactiveForm;
}


/*************************************************************************
 *
 *       Refresca un formulari
 *
 *       Funcio:
 *           void eosFormsRefresh(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm   : El handler del formulari
 *
 *************************************************************************/

void eosFormsRefresh(
    eosHForm hForm) {
    
    eosFormsMessage message;
    
    message.id = MSG_PAINT;
    message.hForm = hForm;
    message.msgPaint.hDisplayService = hForm->hService->hDisplayService;
    eosFormsSendMessage(hForm->hService, &message);
}


/*************************************************************************
 *
 *       Obte les dades privades del formulari
 *
 *       Funcio:
 *           void *eosFormsGetPrivateData(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm: El handler del formulari
 *
 *       Retorn:
 *           Punter a les dades privades
 *
 *************************************************************************/

void *eosFormsGetPrivateData(
    eosHForm hForm) {

    return hForm->privateData;
}


eosHForm eosFormsGetParent(
    eosHForm hForm) {

    return hForm->hParent;
}


/*************************************************************************
 *
 *       Envia un missatge a la cua
 *
 *       Funcio:
 *           void eosFormsSendMessage(
 *              eosHFormsService hService,
 *              eosFormsMessage *message)
 *
 *       Entrada:
 *           hService: El handler del servei
 *           message : El missatge
 *
 *************************************************************************/

void eosFormsSendMessage(
    eosHFormsService hService,
    eosFormsMessage *message) {

    eosQueuePut(hService->hQueue, message);
}


/*************************************************************************
 *
 *       Obte un missatge de la cua
 *
 *       Funcio:
 *           bool eosFormsGetMessage(
 *              eosHFormsService hService,
 *              eosFormsMessage *message)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *       Sortida:
 *           message: El missatge retornat
 *
 *       Retorn:
 *           True si tot es correxte, false en cas d'error o no quedin
 *           mes missatges
 *
 *************************************************************************/

bool eosFormsGetMessage(
    eosHFormsService hService,
    eosFormsMessage *message) {

    return eosQueueGet(hService->hQueue, message);
}
