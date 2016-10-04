#include "eos.hpp"
#include "System/Core/eosQueue.hpp"
#include "Services/eosDigOutput.hpp"
#include "HAL/halGPIO.h"


using namespace eos;


static const char *serviceName = "DigOutputService";
static const unsigned taskStackSize = 512;
static const unsigned commandQueueSize = 10;
static const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param application: L'aplicacio a la que pertany.
///
DigOutputService::DigOutputService(
    Application *application) :
    
    Service(application, serviceName, taskStackSize, taskPriority),
    commandQueue(commandQueueSize) {
}


/// ----------------------------------------------------------------------
/// \brief Afegeig una sortida al servei.
/// \param output: La sortida a afeigir.
///
void DigOutputService::add(
    DigOutput *output) {
    
    if ((output != nullptr) && (output->service == nullptr)) {
        outputs.add(output);
        output->service = this;
    }
}


/// ----------------------------------------------------------------------
/// \brief Elimina una sourtida del servei.
/// \param output: La sortida a eliminar.
///
void DigOutputService::remove(
    DigOutput *output) {
    
    if ((output != nullptr) && (output->service == this)) {
        output->service = nullptr;
        outputs.remove(outputs.indexOf(output));
    }
}


/// ----------------------------------------------------------------------
/// \brief Executa la tasca de control de servei.
/// \param task: La tasca que s'esta executant.
///
void DigOutputService::run(
    Task *task) {
    
    while (true) {
        
        Command command;
        if (commandQueue.get(command, (unsigned) -1)) {
            switch (command.action) {
                case Action::clear:
                    doClearAction(command.output);
                    break;
                    
                case Action::set:
                    doSetAction(command.output);
                    break;
                    
                case Action::toggle:
                    doToggleAction(command.output);
                    break;
                    
                case Action::pulse: 
                    doPulseAction(command.output, command.time);
                    break;
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief  Procesa l'accio 'clear'.
/// \param  output: La sortida.
///
 void DigOutputService::doClearAction(
    DigOutput *output) {
    
    Task::enterCriticalSection();

    // Si estava en un puls, para el temporitzador
    //
    if (output->timer != nullptr) 
        output->timer->stop(1000);
    
    halGPIOPinSetState(output->pin, output->inverted);    

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'accio 'set'.
/// \param output: La sortida.
///
 void DigOutputService::doSetAction(
    DigOutput *output) {

    Task::enterCriticalSection();

    // Si estava en un puls, para el temporitzador
    //
    if (output->timer != nullptr) 
        output->timer->stop(1000);

    halGPIOPinSetState(output->pin, !output->inverted);    

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'accio 'toggle'.
/// \param output: La sortida.
///
void DigOutputService::doToggleAction(
    DigOutput *output) {

    Task::enterCriticalSection();

    // Si estava en un puls, para el temporitzador
    //
    if (output->timer != nullptr) 
        output->timer->stop(1000);

    halGPIOPinToggleState(output->pin);    

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Procesa l'accio 'pulse'.
/// \param output: La sortida.
/// \param time: La durada del puls.
///
void DigOutputService::doPulseAction(
    DigOutput *output, 
    unsigned time) {

    Task::enterCriticalSection();

    // Si no te timer asociat, el crea de nou
    //
    if (output->timer == nullptr) {
        output->timer = new Timer();
        output->timer->setEvTimeout<DigOutputService>(this, &DigOutputService::onTimeout);
        output->timer->setTag(output);
    }
    
    // Si el timer no es actiu, inverteix el pin
    //
    if (!output->timer->isActive())
        halGPIOPinToggleState(output->pin);
    
    // Inicia el timer
    //
    output->timer->start(time, 0);   

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Procesa el timeout del temporitzador pels pulsos.
/// \param timer: El temporitzador.
///
void DigOutputService::onTimeout(
    Timer *timer) {
    
    DigOutput *output = (DigOutput*) timer->getTag();
    halGPIOPinToggleState(output->pin);
}


/// ----------------------------------------------------------------------
/// \brief Assigna l'estat d'una sortida.
/// \param output: La sortida.
/// \param state: L'estat a asignar.
///
void DigOutputService::set(
    DigOutput *output,
    bool state) {
    
    if (output->get() != state) {
        Command command;
        command.action = state ? Action::set : Action::clear;
        command.output = output;
        commandQueue.put(command, (unsigned) -1);
    }
}


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat d'una sortida.
/// \param output: La sortida.
///
void DigOutputService::toggle(
    DigOutput *output) {

    Command command;
    command.action = Action::toggle;
    command.output = output;
    commandQueue.put(command, (unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat d'una sortida en un puls.
/// \param output: La sortida.
/// \param time: La durada del puls.
///
void DigOutputService::pulse(
    DigOutput *output,
    unsigned time) {
    
    Command command;
    command.action = Action::pulse;
    command.output = output;
    command.time = time;
    commandQueue.put(command, (unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei as que s'asignara la sortida.
/// \param pin: Identificador del pin. (Depend de cada hardware en particular).
/// \param inverted: True si treballa amb logica negativa.
///
DigOutput::DigOutput(
    DigOutputService *_service,
    uint8_t _pin,
    bool _inverted):
    service(nullptr),
    pin(_pin),
    inverted(_inverted),
    timer(nullptr) {

    halGPIOPinSetState(pin, inverted);
    halGPIOPinSetModeOutput(pin, false);    

    if (_service != nullptr)
        _service->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigOutput::~DigOutput() {
    
    if (service != nullptr)
        service->remove(this);
    
    if (timer != nullptr)
        delete timer;
}


/// ----------------------------------------------------------------------
/// \brief Obte actual l'estat d'una sortida.
/// \return L'estat de la sortida.
///
bool DigOutput::get() const {

    bool state = halGPIOPinGetState(pin);
    return inverted ? !state : state;
}
