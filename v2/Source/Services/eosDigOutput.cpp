#include "eos.hpp"
#include "System/Core/eosQueue.hpp"
#include "System/Core/eosTimer.hpp"
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
    Application *application):

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
/// \brief Elimina una sortida del servei.
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

    halGPIOClearPin(output->port, output->pin);

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

    halGPIOSetPin(output->port, output->pin);

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

    halGPIOTogglePin(output->port, output->pin);

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
        halGPIOTogglePin(output->port, output->pin);

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
    halGPIOTogglePin(output->port, output->pin);
}


/// ----------------------------------------------------------------------
/// \brief Assigna l'estat actiu a una sortida.
/// \param output: La sortida.
///
void DigOutputService::set(
    DigOutput *output) {

    if (!output->get()) {
        Command command;
        command.action = Action::set;
        command.output = output;
        commandQueue.put(command, (unsigned) -1);
    }
}

/// ----------------------------------------------------------------------
/// \brief Assigna l'estat inactiu a una sortida.
/// \param output: La sortida.
///
void DigOutputService::clear(
    DigOutput *output) {

    if (output->get()) {
        Command command;
        command.action = Action::clear;
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
/// \param port: Identificador del port.
/// \param pin: Identificador del pin.
/// \param inverted: True si treballa amb logica negativa.
///
DigOutput::DigOutput(
    DigOutputService *service,
	GPIOPort port,
    GPIOPin pin):

    service(nullptr),
	timer(nullptr),
	port(port),
    pin(pin) {

    halGPIOInitializePin(port, pin, HAL_GPIO_DIRECTION_OUTPUT);
    halGPIOClearPin(port, pin);

    if (service != nullptr)
        service->add(this);
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

    return halGPIOReadPin(port, pin);
}
