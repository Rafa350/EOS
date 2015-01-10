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
    eosHForm hPrevForm;                // -Anterior form de la llista
    eosHForm hParent;                  // -Handler del form pare
    eosFormsOnMessageCallback onMessage;    // -Callback de cada missatge
    bool needRedraw;                   // -Indica si cal redibuixar
    bool needDestroy;                  // -Indica si cal destruirlo
    void *privateData;                 // -Dades privades del formulari
} Form;

typedef struct __eosFormsService {     // Dades del servei
    ServiceStates state;               // -Estat del servei
    axDisplayServiceHandle hDisplayService; // -Servei de display
    eosFormsOnMessageCallback onMessage;    // -Calback en cada missatge
    eosHQueue hQueue;                  // -Cua de missatges
    eosHForm hActiveForm;              // -Formulari actiu
    eosHForm hFirstForm;               // -Primer form de la llista
    eosHForm hLastForm;                // -Ultim form de la llista
    bool redrawPending;                // -Hi han forms pendents de redibuixar
    bool destroyPending;               // -Hi han forms pendents de destruir
} FormsService;


static void processMessages(eosHFormsService hService);
static void processRedraw(eosHFormsService hService);
static void processDestroy(eosHFormsService hService);


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
    hService->hLastForm = NULL;
    hService->hActiveForm = NULL;
    hService->redrawPending = false;
    hService->destroyPending = false;

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

        case serviceRunning: 
            processMessages(hService);
            processRedraw(hService);
            processDestroy(hService);
            break;
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
    hForm->hService = hService;
    hForm->needDestroy = false;
    hForm->needRedraw = false;
    
    if (hService->hFirstForm == NULL) {
        hService->hFirstForm = hForm;
        hService->hLastForm = hForm;
        hForm->hNextForm = NULL;
        hForm->hPrevForm = NULL;
    }
    else {
        hForm->hNextForm = NULL;
        hForm->hPrevForm = hService->hLastForm;
        hService->hLastForm->hNextForm = hForm;
        hService->hLastForm = hForm;
    }

    eosFormsMessage message;
    message.id = MSG_CREATE;
    message.hForm = hForm;
    message.msgCreate.privateParams = params->privateParams;
    message.msgCreate.privateData = hForm->privateData;
    eosFormsSendMessage(hService, &message);

    return hForm;
}


/*************************************************************************
 *
 *       Destrueix un form
 *
 *       Funcio:
 *          void eosFormsDestroyForm(
 *              eosHForm hForm)
 *
 *       Entrada:
 *           hForm: El handler del form
 *
 *************************************************************************/

void eosFormsDestroyForm(
    eosHForm hForm) {

    eosHFormsService hService = hForm->hService;

    if (hService->hActiveForm == hForm)
        eosFormsSetActiveForm(NULL);
    hForm->needRedraw = false;
    hForm->needDestroy = true;
    hService->destroyPending = true;

    eosFormsMessage message;
    message.id = MSG_DESTROY;
    message.hForm = hForm;
    eosFormsSendMessage(hService, &message);
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

eosHForm __attribute__ ((always_inline)) eosFormsGetActiveForm(
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

void __attribute__ ((always_inline)) eosFormsRefresh(
    eosHForm hForm) {

    hForm->needRedraw = true;
    hForm->hService->redrawPending = true;
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

void *  __attribute__ ((always_inline)) eosFormsGetPrivateData(
    eosHForm hForm) {

    return hForm->privateData;
}


/*************************************************************************
 *
 *       Obte el form pare
 *
 *       Funcio:
 *           eosHForm  eosFormsGetParent(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm: El handler del form
 *
 *       Retorn:
 *           El handler del form pare
 *
 *************************************************************************/

eosHForm  __attribute__ ((always_inline)) eosFormsGetParent(
    eosHForm hForm) {

    return hForm->hParent;
}


/*************************************************************************
 *
 *       Obte el handler del servei
 *
 *       Funcio:
 *           eosHFormsService  eosFormsGetService(
 *               eosHForm hForm)
 *
 *       Entrada:
 *           hForm: El handler del form
 *
 *       Retorn:
 *           EL handler del servei
 *
 *************************************************************************/

eosHFormsService  __attribute__ ((always_inline)) eosFormsGetService(
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
 *       Procesa els missatges pendents en la cua de missatges
 *
 *       Funcio:
 *           void processMessages(
 *               eosHFormsService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

static void processMessages(
    eosHFormsService hService) {

    eosFormsMessage message;
    while (eosQueueGet(hService->hQueue, &message)) {

        if (hService->onMessage != NULL)
            hService->onMessage(hService, &message);

        if (message.id != MSG_NULL) {
            eosHForm hForm = message.hForm;
            if ((hForm != NULL) &&  (hForm->onMessage != NULL))
                hForm->onMessage(hService, &message);
        }
    }
}


/*************************************************************************
 *
 *       Procesa les ordres de redibuix dels forms
 *
 *       Funcio:
 *           void processRedraw(
 *               eosHFormsService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

static void processRedraw(
    eosHFormsService hService) {

    if (hService->redrawPending) {
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
        hService->redrawPending = false;
    }
}


/*************************************************************************
 *
 *       Procesa les ordres de destruccio dels forms
 *
 *       Funcio:
 *           void processRedraw(
 *               eosHFormsService hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

static void processDestroy(
    eosHFormsService hService) {

    if (hService->destroyPending) {

        bool done;
    
        do {
            done = true;
            eosHForm hForm = hService->hFirstForm;
            while (hForm && done) {
                if (hForm->needDestroy) {
                    done = false;

                    if (hForm->hNextForm)
                        hForm->hNextForm->hPrevForm = hForm->hPrevForm;
                    else
                        hService->hLastForm = hForm->hPrevForm;

                    if (hForm->hPrevForm)
                        hForm->hPrevForm->hNextForm = hForm->hNextForm;
                    else
                        hService->hFirstForm = hForm->hNextForm;

                    eosFree(hForm);
                }
                else
                    hForm = hForm->hNextForm;
            }

        } while (!done);
        
        hService->destroyPending = false;
    }
}