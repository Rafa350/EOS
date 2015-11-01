#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "System/eosQueue.hpp"
#include "System/eosTask.hpp"


using namespace eos;


const unsigned messageQueueSize = 20;
const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           bool FormsService::FormsService()
 *
 *************************************************************************/

FormsService::FormsService() :
    task(taskStackSize, taskPriority, this),
    messageQueue(messageQueueSize) {
}


/*************************************************************************
 *
 *       Afegeix un form al servei
 * 
 *       Funcio:
 *           void FormsService::add(
 *               Form *form) 
 * 
 *       Entrada:
 *           form: El form a afeigir
 *
 *************************************************************************/

void FormsService::add(
    Form *form) {
    
    forms.add(form);
}


/*************************************************************************
 *
 *       Tasca de control del servei
 * 
 *       Funcio:
 *           void FormsService::run() 
 *
 *************************************************************************/

void FormsService::run() {
    
    while (true) {
        
        // Procesa els missatges en la cua
        //
        Message message;
        if (messageQueue.get(message, 1000)) {
            
        }
        
        // Procesa el repintat
        //
        FormListIterator iterator(forms);
        while (!iterator.isEnd()) {
            Form *form = iterator.current();
            if (form->paintPending)
                form->paint();
        }
    }
}


/*************************************************************************
 *
 *       Canvia el formulari actiu
 *
 *       Funcio:
 *           Form *FormsService::activate(
 *               Form *form)
 *
 *       Entrada:
 *           form El formulari a activat. NULL si no es vol activar cap
 * 
 *       Retorn:
 *           El form previament actiu
 * 
 *       Notes:
 *           Es genera un event onDeactivate en el form a desactivar i un
 *           event onActivate en el form a activar
 *
 *************************************************************************/

Form *FormsService::activate(
    Form *form) {
    
    Form *inactiveForm = activeForm;
    
    if ((inactiveForm != nullptr) && (inactiveForm->onDeactivate != nullptr))
        inactiveForm->onDeactivate(form);
    
    activeForm = form;

    if ((form != nullptr) && (form->onActivate != nullptr))
        form->onActivate(inactiveForm);
}


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           Form::Forms(
 *               FormsService *service,
 *               Form *parent)
 *
 *       Entrada:
 *           service: El servei
 *           parent : El form pare
 *
 *************************************************************************/

Form::Form(
    FormsService *service,
    Form *parent) {

    service->add(this);
    
    this->parent = parent;
    paintPending = true;
}


/*************************************************************************
 *
 *       Refresca un formulari
 *
 *       Funcio:
 *           void Form::refresh()
 *
 *************************************************************************/

void Form::refresh() {
    
    if (!paintPending) {
        paintPending = true;   
        //eosQueuePut(hForm->hService->hPaintQueue, &hForm, 0);
    }
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
