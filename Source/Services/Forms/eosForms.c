#include "Services/eosForms.h"
#include "System/eosQueue.h"
#include "System/eosMemory.h"


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -Procesat de missatges
} ServiceStates;

typedef struct __eosForm {             // Dades del formulari
    eosHFormsService hService;         // -Handler del servei
    eosHForm hNextForm;                // -Seguent form de la llista
    eosHForm hParent;                  // -Handler del form pare
    eosFormsOnMessageCallback onMessage;    // -Callback de cada missatge
    bool needRedraw;                   // -Indica si cal redibuixar
    void *privateData;                 // -Dades privades del formulari
} Form;

typedef struct __eosFormsService {     // Dades del servei
    ServiceStates state;               // -Estat del servei
    axHDisplayService hDisplayService; // -Servei de display
    eosFormsOnMessageCallback onMessage;    // -Calback en cada missatge
    eosHQueue hQueue;                  // -Cua de missatges
    eosHForm hActiveForm;              // -Formulari actiu
    eosHForm hFirstForm;               // -Primer formulari de la llista
} FormsService;


static bool eosFormsGetMessage(eosHFormsService hService, eosFormsMessage *message);


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

    eosHFormsService hService = eosAlloc(sizeof(FormsService));
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

            // Espera que el servei de display estigui preparat
            //
            if (axDisplayServiceIsReady(hService->hDisplayService))
                hService->state = serviceRunning;
            break;

        case serviceRunning: {

            // Procesa els missatges
            //
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

            // Procesa les ordres de redibuix de la pantalla
            //
            eosHForm hForm = hService->hFirstForm;
            while (hForm) {
                if (hForm->needRedraw) {
                    eosFormsMessage message;
                    message.id = MSG_PAINT;
                    message.hForm = hForm;
                    message.msgPaint.hDisplayService = hService->hDisplayService;
                    eosFormsSendMessage(hService, &message);
                    hForm->needRedraw = false;
                }
                hForm = hForm->hNextForm;
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

    eosHForm hForm = eosAlloc(sizeof(Form) + params->privateDataSize);
    if (hForm == NULL)
        return NULL;

    hForm->hParent = params->hParent;
    if (params->privateDataSize > 0)
        hForm->privateData = (BYTE*) hForm + sizeof(Form);
    else
        hForm->privateData = NULL;
    hForm->onMessage = params->onMessage;
    hForm->hNextForm = hService->hFirstForm;
    hForm->hService = hService;
    hService->hFirstForm = hForm;

    eosFormsMessage message;
    message.id = MSG_INITIALIZE;
    message.hForm = hForm;
    message.msgInitialize.privateParams = params->privateParams;
    message.msgInitialize.privateData = hForm->privateData;
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
 *           hForm: El formulari a activat
 *
 *************************************************************************/

void eosFormsSetActiveForm(
    eosHForm hForm) {
    
    eosHFormsService hService = hForm->hService;

    eosHForm hInactiveForm = hService->hActiveForm;
    if (hInactiveForm != NULL) {
        eosFormsMessage message;
        message.id = MSG_DEACTIVATE;
        message.hForm = hInactiveForm;
        message.msgDeactivate.hNewActive = hForm;
        eosFormsSendMessage(hService, &message);
    }
    
    hService->hActiveForm = hForm;

    if (hForm != NULL) {
        eosFormsMessage message;
        message.id = MSG_ACTIVATE;
        message.hForm = hForm;
        message.msgActivate.hOldActive = hInactiveForm;
        eosFormsSendMessage(hService, &message);
    }
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

    hForm->needRedraw = true;
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


eosHFormsService eosFormsGetService(
    eosHForm hForm) {

    return hForm->hService;
}


/*************************************************************************
 *
 *       Envia un missatge a la cua
 *
 *       Funcio:
 *           void eosFormsPostMessage(
 *              eosHFormsService hService,
 *              eosFormsMessage *message)
 *
 *       Entrada:
 *           hService: El handler del servei
 *           message : El missatge
 *
 *************************************************************************/

void eosFormsPostMessage(
    eosHFormsService hService,
    eosFormsMessage *message) {

    eosQueuePut(hService->hQueue, message);
}


/*************************************************************************
 *
 *       Envia un missatge directament al form
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

    message->hForm->onMessage(hService, message);
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
