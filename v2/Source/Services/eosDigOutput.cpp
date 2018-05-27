#include "eos.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosTimer.h"
#include "Services/eosDigOutput.h"
#include "hal/halGPIO.h"
#include "osal/osalThread.h"


using namespace eos;


static const char *serviceName = "DigOutputService";
static const unsigned taskStackSize = 512;
static const unsigned commandQueueSize = 10;
static const TaskPriority taskPriority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param application: L'aplicacio a la que pertany.
/// \param info: Parametres d'inicialitzacio.
///
DigOutputService::DigOutputService(
    Application *application,
    const DigOutputServiceInitializeInfo *info):

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
                    doClearCommand(&command);
                    break;

                case Action::set:
                    doSetCommand(&command);
                    break;

                case Action::toggle:
                    doToggleCommand(&command);
                    break;

                case Action::pulse:
                    doPulseCommand(&command);
                    break;

                case Action::delayedClear:
                case Action::delayedSet:
                case Action::delayedToggle:
                	break;

                case Action::delayedPulse:
                    doDelayedPulseCommand(&command);
                    break;
            }
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief  Procesa la comanda 'clear'.
/// \param  Command: La comanda a procesar
///
 void DigOutputService::doClearCommand(
    Command *command) {

    osalEnterCritical();

    if (command->output->state != DigOutput::State::Done)
    	stopTimer(command->output);

    halGPIOClearPin(command->output->port, command->output->pin);
    command->output->state = DigOutput::State::Done;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Procesa la comanda 'set'.
/// \param command: La comanda a procesar.
///
 void DigOutputService::doSetCommand(
    Command *command) {

	osalEnterCritical();

    if (command->output->state != DigOutput::State::Done)
    	stopTimer(command->output);

    halGPIOSetPin(command->output->port, command->output->pin);
    command->output->state = DigOutput::State::Done;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Procesa la comanda 'toggle'.
/// \param command: La comanda a procesar.
///
void DigOutputService::doToggleCommand(
    Command *command) {

    osalEnterCritical();

    if (command->output->state != DigOutput::State::Done)
    	stopTimer(command->output);

    halGPIOTogglePin(command->output->port, command->output->pin);
    command->output->state = DigOutput::State::Done;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Procesa la comanda 'pulse'.
/// \param command: La comanda a procesar.
///
void DigOutputService::doPulseCommand(
    Command *command) {

    Task::enterCriticalSection();

    if (command->output->state == DigOutput::State::Done)
        halGPIOTogglePin(command->output->port, command->output->pin);

    startTimer(command->output, command->width);
    command->output->state = DigOutput::State::Pulse;

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------ç
/// \brief Procesa la comanda 'delayedPulse'
/// \param command: La comanda a procesar.
///
void DigOutputService::doDelayedPulseCommand(
	Command *command) {

    Task::enterCriticalSection();

    startTimer(command->output, command->delay);
    command->output->time = command->width;
    command->output->state = DigOutput::State::Delay;

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Inicia el temporitzador.
/// \param output: La sortida.
/// \param time: El temps.
///
void DigOutputService::startTimer(
	DigOutput *output,
	unsigned time) {

	if (output->timer == nullptr) {
		output->timer = new Timer();
		output->timer->setEvTimeout<DigOutputService>(this, &DigOutputService::onTimeout);
		output->timer->setTag(output);
	}
	output->timer->start(time, 0);
}


/// ----------------------------------------------------------------------
/// \brief Para el temporitzador.
/// \param output: la sortida.
///
void DigOutputService::stopTimer(
	DigOutput *output) {

	if (output->timer != nullptr)
		output->timer->stop((unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief Procesa el timeout del temporitzador.
/// \param timer: El temporitzador.
///
void DigOutputService::onTimeout(
    Timer *timer) {

    DigOutput *output = (DigOutput*) timer->getTag();

    switch (output->state) {
    	case DigOutput::State::Done:
    		break;

    	case DigOutput::State::Pulse:
    	    halGPIOTogglePin(output->port, output->pin);
    	    stopTimer(output);
    		output->state = DigOutput::State::Done;
    		break;

    	case DigOutput::State::Delay:
    	    halGPIOTogglePin(output->port, output->pin);
    	    startTimer(output, output->time);
    		output->state = DigOutput::State::Pulse;
    		break;
    }
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
/// \param width: La amplada del puls en ticks.
///
void DigOutputService::pulse(
    DigOutput *output,
    unsigned width) {

    Command command;
    command.action = Action::pulse;
    command.output = output;
    command.width = width;
    commandQueue.put(command, (unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat d'una sortida en un puls retardat.
/// \param output: La sortida.
/// \param delay: El retard en ticks.
/// \param width: La amplada del puls en ticks.
///
void DigOutputService::delayedPulse(
	DigOutput *output,
	unsigned delay,
	unsigned width) {

    Command command;
    command.action = Action::delayedPulse;
    command.output = output;
    command.delay = delay;
    command.width = width;
    commandQueue.put(command, (unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param service: El servei al que s'asignara la sortida.
/// \param info: Parametres d'inicialitzacio.
///
DigOutput::DigOutput(
    DigOutputService *service,
    const DigOutputInitializeInfo *info):

    service(nullptr),
	timer(nullptr),
	time(0),
	state(State::Done),
	port(info->port),
    pin(info->pin) {

    GPIOInitializePinInfo pinInfo;
    pinInfo.port = info->port;
    pinInfo.pin = info->pin;
    pinInfo.options =
        (info->openDrain ? HAL_GPIO_MODE_OUTPUT_OD : HAL_GPIO_MODE_OUTPUT_PP) |
        (info->initState ? HAL_GPIO_INIT_SET : HAL_GPIO_INIT_CLR);
    halGPIOInitializePin(&pinInfo);

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


/// ----------------------------------------------------------------------
/// \brief Obte l'estat del port.
/// \return L'estat del port.
///
DigOutput::State DigOutput::getState() const {

	State s;

	Task::enterCriticalSection();
	s = state;
	Task::exitCriticalSection();

	return s;
}
