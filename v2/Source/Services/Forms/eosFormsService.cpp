#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "System/Collections/eosQueue.hpp"
#include "Services/Forms/eosForms.hpp"


using namespace eos;


const unsigned taskStackSize = 512;
const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param mssageQueue: La cua de missatges
/// \param display: Controlador de pantalla
///
FormsService::FormsService(
    MessageQueueHandle _messageQueue,
    FormsDisplayHandle _display) :
    task(taskStackSize, taskPriority, this),
    messageQueue(_messageQueue),
    display(_display) {
}


/// ----------------------------------------------------------------------
/// \brief Desctructor.
///
FormsService::~FormsService() {
    
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un form al servei
/// \param form: El form a afeigir
///
void FormsService::add(
    FormHandle form) {
    
    forms.add(form);
    form->service = this;
}


/// ----------------------------------------------------------------------
/// \brief Elimina un form del servei.
/// \param form: El form a eliminar.
///
void FormsService::remove(
    FormHandle form) {
    
    form->service = nullptr;
    forms.remove(forms.indexOf(form));
}


/// ----------------------------------------------------------------------
/// \brief Marca un form per la seva destruccio.
/// \param form: El form a destruir.
///
void FormsService::destroy(
    FormHandle form) {
    
    destroyForms.add(form);
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
            
        /*
        // Procesa l'eliminacio de forms pendents de destruccio
        //
        if (destroyForms.getCount() > 0) {
            FormListIterator iterator(destroyForms);
            
            while (iterator.hasNext()) {
                forms.remove(forms.indexOf(iterator.current()));
                iterator.next();
            }
            
            iterator.first();
            while (iterator.hasNext()) {
                iterator.next();
            }
            
            destroyForms.clear();
        }
        */
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
/// \brief Refresca un formulari. Es genera un missatge MSG_PAINT.
/// \param form: El formulari a refrescar
///
void FormsService::refresh(
    FormHandle form) {
    
    Message msg;
    
    msg.id = MSG_PAINT;
    msg.target = form;
    msg.msgPaint.display = display;
    
    messageQueue->put(msg, (unsigned) -1);
}