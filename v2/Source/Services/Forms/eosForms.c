#include "eos.h"

#include "Services/Forms/eosForms.h"
#include "System/eosQueue.h"
#include "System/eosTask.h"
#include "System/eosMemory.h"


typedef struct __eosForm {             // Dades del formulari
    eosFormsServiceHandle hService;    // -Handler del servei
    eosFormHandle hNextForm;           // -Seguent form de la llista
    eosFormHandle hPrevForm;           // -Anterior form de la llista
    eosFormHandle hParent;             // -Handler del form pare
    eosFormsOnMessageCallback onMessage;    // -Event onMessage
    eosFormsOnPaintCallback onPaint;   // -Event onPaint
    bool paintPending;                 // -Indica si esta pendent de pinter
    bool destroyPending;               // -Indica si esta pendent de destruir
    void *privateData;                 // -Dades privades del formulari
} eosForm;

typedef struct __eosFormsService {     // Dades del servei
    eosDisplayHandle hDisplay;         // -Handler del display
    eosFormsOnMessageCallback onMessage;    // -Event onMessage
    eosTaskHandle hTask;               // -Tasca del servei
    eosQueueHandle hMessageQueue;      // -Cua de missatges
    eosQueueHandle hPaintQueue;        // -Cua de repintat
    eosFormHandle hActiveForm;         // -Formulari actiu
    eosFormHandle hFirstForm;          // -Primer form de la llista
    eosFormHandle hLastForm;           // -Ultim form de la llista
} eosFormsService;


static void task(void *params);


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

eosFormsServiceHandle eosFormsServiceInitialize(
    eosFormsServiceParams *params) {

    eosDebugVerify(params != NULL);

    eosFormsServiceHandle hService = eosAlloc(sizeof(eosFormsService));
    if (hService != NULL) {

        hService->hDisplay = params->hDisplay;
        hService->onMessage = params->onMessage;
        hService->hFirstForm = NULL;
        hService->hLastForm = NULL;
        hService->hActiveForm = NULL;

        // -Crea la cua de missatges
        //
        hService->hMessageQueue = eosQueueCreate(sizeof(eosFormsMessage), 100);
        eosDebugVerify(hService->hMessageQueue != NULL);

        // -Crea la cua de forms pendents de repintat
        //
        hService->hPaintQueue = eosQueueCreate(sizeof(eosFormHandle), 10);
        eosDebugVerify(hService->hPaintQueue != NULL);
        
        // -Crea la tasca de control del servei
        //
        hService->hTask = eosTaskCreate(0, 1024, task, hService);
        eosDebugVerify(hService->hTask != NULL);
    }
    
    return hService;
}


/*************************************************************************
 *
 *       Crea un form
 *
 *       Funcio:
 *           eosFormHandle eosFormsCreateForm(
 *               eosFormsServiceHandle hService,
 *               eosFormParams *params)
 *
 *       Entrada:
 *           hService: Handler del servei
 *           params  : Parametres d'inicialitzacio
 *
 *       Retorn:
 *           El handler del form, NULL en cas d'error
 *
 *************************************************************************/

eosFormHandle eosFormsCreateForm(
    eosFormsServiceHandle hService,
    eosFormParams *params) {
    
    eosDebugVerify(params != NULL);

    eosFormHandle hForm = eosAlloc(sizeof(eosForm) + params->privateDataSize);
    if (hForm != NULL) {

        hForm->hParent = params->hParent;
        if (params->privateDataSize > 0)
            hForm->privateData = (void*) ((uint8_t*) hForm + sizeof(eosForm));
        else
            hForm->privateData = NULL;
        hForm->onMessage = params->onMessage;
        hForm->destroyPending = false;
        hForm->paintPending = false;

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
    }
    
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
    
    eosDebugVerify(hForm != NULL);

    if (!hForm->destroyPending) {
        hForm->destroyPending = true;
        eosFormsServiceHandle hService = hForm->hService;
        if (hService->hActiveForm == hForm)
            eosFormsSetActiveForm(hService, NULL);
    }
}


/*************************************************************************
 *
 *       Obte el formulari actiu
 *
 *       Funcio:
 *           eosFormHandle eosFormsGetActiveForm(
 *               eosFormsServiceHandle hService)
 *
 *       Entrada:
 *           hService: Handler del servei
 * 
 *       Retorn:
 *           El handler del formulari actiu
 *
 **************************************************************************/

eosFormHandle eosFormsGetActiveForm(
    eosFormsServiceHandle hService) {
    
    eosDebugVerify(hService != NULL);

    return hService->hActiveForm;
}


/*************************************************************************
 *
 *       Canvia el formulari actiu
 *
 *       Funcio:
 *           eosFormHandle eosFormsSetActiveForm(
 *               eosFormsServiceHandle hService,
 *               eosFormHandle hForm)
 *
 *       Entrada:
 *           hService: El handler del servei
 *           hForm   : El formulari a activat
 *
 *************************************************************************/

void eosFormsSetActiveForm(
    eosFormsServiceHandle hService,
    eosFormHandle hForm) {
    
    eosDebugVerify(hService != NULL);
    
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

    eosDebugVerify(hForm != NULL);
    
    if (!hForm->paintPending) {
        hForm->paintPending = true;   
        eosQueuePut(hForm->hService->hPaintQueue, &hForm, 0);
    }
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
 *           eosFormHandle eosFormsGetParent(
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

    eosQueuePut(message->hForm->hService->hMessageQueue, message, 0);
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
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void task(
 *               void *params)
 * 
 *       Entrada:
 *           params: Parametres de la tasca (hService)
 *
 *************************************************************************/

static void task(
    void *params) {
    
    eosFormHandle hForm;
    eosFormsServiceHandle hService = params;

    while (true) {

        // Procesa els missatges de la cua
        //
        eosFormsMessage message;
        while (eosQueueGet(hService->hMessageQueue, &message, 0)) {

            if (hService->onMessage != NULL)
                hService->onMessage(&message);

            if (message.id != MSG_NULL) {
                hForm = message.hForm;
                if ((hForm != NULL) &&  (hForm->onMessage != NULL))
                    hForm->onMessage(&message);
            }
        }
        
        // Procesa el repintat pendent
        //
        while (eosQueueGet(hService->hPaintQueue, &hForm, 0)) {
            if ((hForm->onPaint != NULL) && !hForm->destroyPending)
                hForm->onPaint(hService->hDisplay);
            hForm->paintPending = false;
        }        
                
        // Procesa la destruccio pendent
        //    
    }
}

