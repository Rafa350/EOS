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
 *           bool FormsService::FormsService(
 *               MessageQueue *messageQueue,
 *               DisplayServiceHandle displayService)
 * 
 *       Entrada:
 *           messageQueue  : La cua de missatges
 *           displayService: Servei de pantalla
 *
 *************************************************************************/

FormsService::FormsService(
    MessageQueue *_messageQueue,
    DisplayServiceHandle _displayService) :
    task(taskStackSize, taskPriority, this),
    messageQueue(_messageQueue),
    displayService(_displayService) {
}


/*************************************************************************
 *
 *       Afegeix un form al servei
 * 
 *       Funcio:
 *           void FormsService::add(
 *               FormHandle form) 
 * 
 *       Entrada:
 *           form: El form a afeigir
 *
 *************************************************************************/

void FormsService::add(
    FormHandle form) {
    
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
        
        // Captura els events dels dispositius d'entrada
        //
        
        // Procesa els missatges en la cua
        //
        Message message;
        if (messageQueue->receive(message, 1000)) 
            message.target->dispatchMessage(message);
        
        // Procesa el repintat
        //
        FormListIterator iterator(forms);
        while (!iterator.isEnd()) {
            FormHandle form = iterator.current();
            if (form->paintPending) {
                form->paintPending = false;
                form->onPaint(displayService);                
            }
        }
    }
}


/*************************************************************************
 *
 *       Canvia el formulari actiu
 *
 *       Funcio:
 *           FormHandle FormsService::activate(
 *               FormHandle form)
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

FormHandle FormsService::activate(
    FormHandle form) {

    if (activeForm != nullptr)    
        activeForm->onDeactivate(form);
    
    FormHandle oldActive = activeForm;
    activeForm = form;

    if (activeForm != nullptr)    
        activeForm->onDeactivate(oldActive);
}


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           Form::Forms(
 *               FormsServiceHandle service,
 *               FormHandle parent)
 *
 *       Entrada:
 *           service: El servei
 *           parent : El form pare
 *
 *************************************************************************/

Form::Form(
    FormsServiceHandle service,
    FormHandle parent) {

    service->add(this);
    
    this->service = service;
    this->parent = parent;
    paintPending = true;
}


/*************************************************************************
 *
 *       Destructor
 *
 *       Funcio:
 *           Form::~Form() 
 * 
 *************************************************************************/

Form::~Form() {
    
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
    
    paintPending = true;   
}


/*************************************************************************
 *
 *       Dibuixa el formulari en pantalla
 * 
 *       Funcio:
 *           void Form::paint(
 *               DisplayServiceHandle displayService) 
 * 
 *       Entrada:
 *           displayService: Servei de pantalla
 *
 *************************************************************************/

void Form::onPaint(
    DisplayServiceHandle displayService) {
    
}


void Form::dispatchMessage(
    Message &message) {
    
    switch (message.id) {
        default:
            break;
    }
}



MessageQueue::MessageQueue():
    queue(sizeof(Message)) {    
}


void MessageQueue::send(
    Message &message,
    unsigned blockTime) {
    
    queue.put(message, blockTime);
}


bool MessageQueue::receive(
    Message &message, 
    unsigned blockTime) {
    
    return queue.get(message, blockTime);
}
