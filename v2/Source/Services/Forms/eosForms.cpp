#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "System/eosQueue.hpp"
#include "System/eosTask.hpp"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param mssageQueue: La cua de missatges
/// \param displayService: Servei de pantalla
///
FormsService::FormsService(
    MessageQueue *_messageQueue,
    DisplayControllerHandle _displayController) :
    task(taskStackSize, taskPriority, this),
    messageQueue(_messageQueue),
    displayController(_displayController) {
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un form al servei
/// \param form: El form a afeigir
///
void FormsService::add(
    FormHandle form) {
    
    forms.add(form);
}


/// ----------------------------------------------------------------------
/// \brief Elimina un form del servei.
/// \param form: El form a eliminar.
///
void FormsService::remove(
    FormHandle form) {
    
}


/// ----------------------------------------------------------------------
/// \brief Tasca de control del servei
///
void FormsService::run() {
    
    while (true) {
        
        // Procesa els missatges en la cua
        //
        Message message;
        if (messageQueue->get(message, (unsigned) -1)) 
            message.target->dispatchMessage(message);
        
        // Procesa el repintat. No mes es pinta el formulari actiu, ja
        // que es pantalla complerta, no finestres
        //
        if ((activeForm != nullptr) && activeForm->paintPending) {
            displayController->beginCommand();
            activeForm->paintPending = false;
            activeForm->onPaint(displayController);
            displayController->addCommandRefresh();
            displayController->endCommand();
        }
        
        // Procesa l'eliminacio de forms pendents de destruccio
        //
    }
}


/// ----------------------------------------------------------------------
/// \brief Canvia el formulari actiu
/// \param form: El formulari a activat. nullptr si no es vol activar cap
///
FormHandle FormsService::activate(
    FormHandle form) {

    if (activeForm != nullptr)    
        activeForm->onDeactivate(form);
    
    FormHandle oldActive = activeForm;
    activeForm = form;

    if (activeForm != nullptr)    
        activeForm->onActivate(oldActive);
}


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param service: El servei de gestio dels forms
/// \param parent: El form pare
///
Form::Form(
    FormsServiceHandle _service,
    FormHandle _parent):
    service(_service),
    parent(_parent),
    paintPending(true),
    destroyPending(false) {

    if (service != nullptr)
        service->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Form::~Form() {
    
    if (service != nullptr)
        service->remove(this);
}


/// ----------------------------------------------------------------------
/// \brief Inicia el proces de destruccio del form.
///
void Form::destroy() {
    
    destroyPending = true;
}


/// ----------------------------------------------------------------------
/// \brief Refresca un formulari.
///
void Form::refresh() {
    
    paintPending = true;   
}


/// ----------------------------------------------------------------------
/// \brief Procesa un missatge.
/// \param message: El missatge a procesar.
///
void Form::dispatchMessage(
    Message &message) {
    
    switch (message.id) {
        default:
            break;
    }
}
