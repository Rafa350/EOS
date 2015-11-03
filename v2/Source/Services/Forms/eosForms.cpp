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
        
        // Captura els events dels dispositius d'entrada
        //
        
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
            if (form->paintPending) {
                form->paintPending = false;
                form->paint();                
            }
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
        inactiveForm->onDeactivate->execute(form);
    
    activeForm = form;

    if ((form != nullptr) && (form->onActivate != nullptr))
        form->onActivate->execute(inactiveForm);
}


/*************************************************************************
 *
 *       Envia un missatge a la cua
 * 
 *       Funcio:
 *           void FormsService::sendMessage(
 *               Message message) 
 * 
 *       Entrada:
 *           message: El missatge a enviar
 *
 *************************************************************************/

void FormsService::sendMessage(
    Message message) {
    
    messageQueue.get(message, 1000);
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
    
    this->service = service;
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
    
    paintPending = true;   
}


/*************************************************************************
 *
 *       Dibuixa el formulari en pantalla
 * 
 *       Funcio:
 *           void Form::paint() 
 *
 *************************************************************************/

void Form::paint() {
    
}