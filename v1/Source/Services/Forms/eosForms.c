#include "Services/eosForms.h"
#include "System/eosQueue.h"
#include "System/eosMemory.h"


typedef enum {                         // Estats del servei
    serviceInitializing,               // -Inicialitzant
    serviceRunning                     // -Procesat de missatges
} ServiceStates;

typedef struct __eosForm {             // Dades del formulari
    eosFormHandle hNextForm;           // -Seguent form de la llista
    eosFormHandle hPrevForm;           // -Anterior form de la llista
    eosFormHandle hParent;             // -Handler del form pare
    eosFormsOnMessageCallback onMessage;    // -Callback de cada missatge
    bool needRedraw;                   // -Indica si cal redibuixar
    bool needDestroy;                  // -Indica si cal destruirlo
    void *privateData;                 // -Dades privades del formulari
} eosForm;

typedef struct __eosFormsService {     // Dades del servei
    ServiceStates state;               // -Estat del servei
    axDisplayServiceHandle hDisplayService; // -Servei de display
    eosFormsOnMessageCallback onMessage;    // -Calback en cada missatge
    eosHQueue hQueue;                  // -Cua de missatges
    eosFormHandle hActiveForm;         // -Formulari actiu
    eosFormHandle hFirstForm;          // -Primer form de la llista
    eosFormHandle hLastForm;           // -Ultim form de la llista
    bool redrawPending;                // -Hi han forms pendents de redibuixar
    bool destroyPending;               // -Hi han forms pendents de destruir
} eosFormsService;


static eosFormsServiceHandle hService = NULL;


static void processMessages(void);
static void processRedraw(void);
static void processDestroy(void);


/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           bool eosFormsServiceInitialize(
 *               eosFormsServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Retorn:
 *           True si tot es correcte
 *
 *************************************************************************/

bool eosFormsServiceInitialize(
    eosFormsServiceParams *params) {

    if (hService)
        return false;

    hService = eosAlloc(sizeof(eosFormsService));
    if (!hService)
        return false;

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
    
    return true;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosFormsServiceTask(void)
 *
 *************************************************************************/

void eosFormsServiceTask(void) {

    switch (hService->state) {
        case serviceInitializing:

            // Espera que el servei de display estigui preparat
            //
            if (axDisplayServiceIsReady(hService->hDisplayService))
                hService->state = serviceRunning;
            break;

        case serviceRunning: 
            processMessages();
            processRedraw();
            processDestroy();
            break;
    }
}


/*************************************************************************
 *
 *       Crea un form
 *
 *       Funcio:
 *           eosFormHandle eosFormsCreateForm(
 *               eosFormParams *params)
 *
 *       Entrada:
 *           params: Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del form, NULL en cas d'error
 *
 *************************************************************************/

eosFormHandle eosFormsCreateForm(
    eosFormParams *params) {

    eosFormHandle hForm = eosAlloc(sizeof(eosForm) + params->privateDataSize);
    if (hForm == NULL)
        return NULL;

    hForm->hParent = params->hParent;
    if (params->privateDataSize > 0)
        hForm->privateData = (void*) ((BYTE*) hForm + sizeof(eosForm));
    else
        hForm->privateData = NULL;
    hForm->onMessage = params->onMessage;
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
    eosFormsSendMessage(&message);

    return hForm;
}


/*************************************************************************
 *
 *       Destrueix un form
 *
 *       Funcio:
 *          void eosFormsDestroyForm(
 *              eosFormHandle hForm)
 *
 *       Entrada:
 *           hForm: El handler del form
 *
 *************************************************************************/

void eosFormsDestroyForm(
    eosFormHandle hForm) {

    if (hService->hActiveForm == hForm)
        eosFormsSetActiveForm(NULL);
    hForm->needRedraw = false;
    hForm->needDestroy = true;
    hService->destroyPending = true;
}


/*************************************************************************
 *
 *       Obte el formulari actiu
 *
 *       Funcio:
 *           eosFormHandle eosFormsGetActiveForm(void)
 *
 *       Retorn:
 *           El handler del formulari actiu
 *
 **************************************************************************/

eosFormHandle eosFormsGetActiveForm(void) {

    return hService->hActiveForm;
}


/*************************************************************************
 *
 *       Canvia el formulari actiu
 *
 *       Funcio:
 *           eosFormHandle eosFormsSetActiveForm(
 *               eosFormHandle hForm)
 *
 *       Entrada:
 *           hForm: El formulari a activat
 *
 *************************************************************************/

void eosFormsSetActiveForm(
    eosFormHandle hForm) {
    
    eosFormHandle hInactiveForm = hService->hActiveForm;
    if (hInactiveForm != NULL) {
        eosFormsMessage message;
        message.id = MSG_DEACTIVATE;
        message.hForm = hInactiveForm;
        message.msgDeactivate.hNewActive = hForm;
        eosFormsSendMessage(&message);
    }
    
    hService->hActiveForm = hForm;

    if (hForm != NULL) {
        eosFormsMessage message;
        message.id = MSG_ACTIVATE;
        message.hForm = hForm;
        message.msgActivate.hOldActive = hInactiveForm;
        eosFormsSendMessage(&message);
    }
}


/*************************************************************************
 *
 *       Refresca un formulari
 *
 *       Funcio:
 *           void eosFormsRefresh(
 *               eosFormHandle hForm)
 *
 *       Entrada:
 *           hForm   : El handler del formulari
 *
 *************************************************************************/

void eosFormsRefresh(
    eosFormHandle hForm) {

    hForm->needRedraw = true;
    hService->redrawPending = true;
}


/*************************************************************************
 *
 *       Obte les dades privades del formulari
 *
 *       Funcio:
 *           void *eosFormsGetPrivateData(
 *               eosFormHandle hForm)
 *
 *       Entrada:
 *           hForm: El handler del formulari
 *
 *       Retorn:
 *           Punter a les dades privades
 *
 *************************************************************************/

void *eosFormsGetPrivateData(
    eosFormHandle hForm) {

    return hForm->privateData;
}


/*************************************************************************
 *
 *       Obte el form pare
 *
 *       Funcio:
 *           eosFormHandle  eosFormsGetParent(
 *               eosFormHandle hForm)
 *
 *       Entrada:
 *           hForm: El handler del form
 *
 *       Retorn:
 *           El handler del form pare
 *
 *************************************************************************/

eosFormHandle  eosFormsGetParent(
    eosFormHandle hForm) {

    return hForm->hParent;
}


/*************************************************************************
 *
 *       Envia un missatge a la cua
 *
 *       Funcio:
 *           void eosFormsPostMessage(
 *              eosFormsMessage *message)
 *
 *       Entrada:
 *           hService: El handler del servei
 *           message : El missatge
 *
 *************************************************************************/

void eosFormsPostMessage(
    eosFormsMessage *message) {

    eosQueuePut(hService->hQueue, message);
}


/*************************************************************************
 *
 *       Envia un missatge directament al form i espera que es procesi
 *
 *       Funcio:
 *           void eosFormsSendMessage(
 *              eosFormsMessage *message)
 *
 *       Entrada:
 *           message: El missatge
 *
 *************************************************************************/

void eosFormsSendMessage(
    eosFormsMessage *message) {

    message->hForm->onMessage(message);
}


/*************************************************************************
 *
 *       Envia un missatge de notificacio directament al form pare
 *
 *       Funcio:
 *           void eosFormsSendNotify(
 *              eosFormHandle hSender,
 *              unsigned event,
 *              void *params)
 *
 *       Entrada:
 *           hSender: Handler del form origen del missatge
 *           event  : El codi de notificacio
 *           params : Parametres de la notificacio
 *
 *************************************************************************/

void eosFormsSendNotify(
    eosFormHandle hSender,
    unsigned event,
    void *params) {

    eosFormsMessage message;

    message.id = MSG_NOTIFY;
    message.hForm = eosFormsGetParent(hSender);
    message.msgNotify.hSender = hSender;
    message.msgNotify.event = event;
    message.msgNotify.params = params;

    eosFormsSendMessage(&message);
}


/*************************************************************************
 *
 *       Envia un missatge de comanda directament al form pare
 *
 *       Funcio:
 *           void eosFormsSendCommand(
 *              eosFormHandle hSender,
 *              unsigned command)
 *
 *       Entrada:
 *           hSender: Handler del form origen del missatge
 *           command: El codi de la comanda
 *
 *************************************************************************/

void eosFormsSendCommand(
    eosFormHandle hSender,
    unsigned command) {

    eosFormsMessage message;

    message.id = MSG_COMMAND;
    message.hForm = eosFormsGetParent(hSender);
    message.msgCommand.command = command;

    eosFormsSendMessage(&message);
}


/*************************************************************************
 *
 *       Procesa els missatges pendents en la cua de missatges
 *
 *       Funcio:
 *           void processMessages(void)
 *
 *************************************************************************/

static void processMessages(void) {

    eosFormsMessage message;
    while (eosQueueGet(hService->hQueue, &message)) {

        if (hService->onMessage != NULL)
            hService->onMessage(&message);

        if (message.id != MSG_NULL) {
            eosFormHandle hForm = message.hForm;
            if ((hForm != NULL) &&  (hForm->onMessage != NULL))
                hForm->onMessage(&message);
        }
    }
}


/*************************************************************************
 *
 *       Procesa les ordres de redibuix dels forms
 *
 *       Funcio:
 *           void processRedraw(void)
 *
 *************************************************************************/

static void processRedraw(void) {

    if (hService->redrawPending) {
        eosFormHandle hForm = hService->hFirstForm;
        while (hForm) {
            if (hForm->needRedraw) {
                eosFormsMessage message;
                message.id = MSG_PAINT;
                message.hForm = hForm;
                message.msgPaint.hDisplayService = hService->hDisplayService;
                eosFormsSendMessage(&message);
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
 *           void processRedraw(void)
 *
 *************************************************************************/

static void processDestroy(void) {

    if (hService->destroyPending) {

        bool done;
    
        do {
            done = true;
            eosFormHandle hForm = hService->hFirstForm;
            while (hForm && done) {
                if (hForm->needDestroy) {
                    done = false;

                    eosFormsMessage message;
                    message.id = MSG_DESTROY;
                    message.hForm = hForm;
                    eosFormsSendMessage(&message);

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
