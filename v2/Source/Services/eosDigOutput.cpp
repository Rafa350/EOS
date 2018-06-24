#include "eos.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosTimer.h"
#include "Services/eosDigOutput.h"
#include "hal/halGPIO.h"
#include "osal/osalTask.h"


using namespace eos;


class DigOutputService::Implementation {
	private:
		enum class Action {
			set,
			clear,
			toggle,
			pulse,
			delayedSet,
			delayedClear,
			delayedToggle,
			delayedPulse
		};
		struct Command {
			Action action;
			DigOutput::Implementation *outputImpl;
			uint16_t delay;
			uint16_t width;
		};

	private:
		Queue<Command> commandQueue;

	public:
		Implementation();
		~Implementation();

		void processCommands();
		void clear(DigOutput *output);
		void set(DigOutput *output);
		void toggle(DigOutput *output);
		void pulse(DigOutput *output, uint16_t width);
		void delayedPulse(DigOutput *output, uint16_t delay, uint16_t width);
};


class DigOutput::Implementation {
	private:
		enum class State {
			Done,
			Delay,
			Pulse
		};

	private:
	    GPIOPort port;
		GPIOPin pin;
		State state;
		Timer *timer;
		uint16_t time;

	public:
		Implementation(const DigOutputInitializeInfo *info);
		~Implementation();

		void set();
		void clear();
		void toggle();
		void pulse(uint16_t width);
		void delayedPulse(uint16_t delay, uint16_t width);
		bool get() const;

		void startTimer(uint16_t time);
		void stopTimer();
		void onTimeout(Timer *timer);
};


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
	pImpl(new DigOutputService::Implementation()) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

	delete pImpl;
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
/// \brief Bucle d'execucio.
///
void DigOutputService::onLoop() {

	pImpl->processCommands();
}


/// ----------------------------------------------------------------------
/// \brief Assigna l'estat actiu a una sortida.
/// \param output: La sortida.
///
void DigOutputService::set(
    DigOutput *output) {

	pImpl->set(output);
}


/// ----------------------------------------------------------------------
/// \brief Assigna l'estat inactiu a una sortida.
/// \param output: La sortida.
///
void DigOutputService::clear(
    DigOutput *output) {

	pImpl->clear(output);
}


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat d'una sortida.
/// \param output: La sortida.
///
void DigOutputService::toggle(
    DigOutput *output) {

	pImpl->toggle(output);
}


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat d'una sortida en un puls.
/// \param output: La sortida.
/// \param width: La amplada del puls en ticks.
///
void DigOutputService::pulse(
    DigOutput *output,
    unsigned width) {

	pImpl->pulse(output, width);
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

	pImpl->delayedPulse(output, delay, width);
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
	pImpl(new Implementation(info)) {

    if (service != nullptr)
        service->add(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigOutput::~DigOutput() {

    if (service != nullptr)
        service->remove(this);

    delete pImpl;
}


/// ----------------------------------------------------------------------
/// \brief Obte actual l'estat d'una sortida.
/// \return L'estat de la sortida.
///
bool DigOutput::get() const {

    return pImpl->get();
}


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
///
DigOutputService::Implementation::Implementation():
	commandQueue(commandQueueSize) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte.
///
DigOutputService::Implementation::~Implementation() {
}


/// -----------------------------------------------------------------
/// \brief Procesa les comandes que hi han a la cua.
///
void DigOutputService::Implementation::processCommands() {

    Command command;

    while (commandQueue.get(command, (unsigned) -1)) {
        switch (command.action) {
            case Action::clear:
            	command.outputImpl->clear();
                break;

            case Action::set:
            	command.outputImpl->set();
                break;

            case Action::toggle:
            	command.outputImpl->toggle();
                break;

            case Action::pulse:
            	command.outputImpl->pulse(command.width);
                break;

            case Action::delayedClear:
            case Action::delayedSet:
            case Action::delayedToggle:
                break;

            case Action::delayedPulse:
            	command.outputImpl->delayedPulse(command.delay, command.width);
                break;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief Envia una comanda CLEAR al servei.
/// \param output: La sortida.
///
void DigOutputService::Implementation::clear(
	DigOutput *output) {

	if (output->get()) {
        Command command;
        command.action = Action::clear;
        command.outputImpl = output->getImpl();
        commandQueue.put(command, (unsigned) -1);
    }
}


/// ----------------------------------------------------------------------
/// \brief Envia una comanda SET al servei.
/// \param output: La sortida.
///
void DigOutputService::Implementation::set(
	DigOutput *output) {

	if (!output->get()) {
        Command command;
        command.action = Action::clear;
        command.outputImpl = output->getImpl();
        commandQueue.put(command, (unsigned) -1);
    }
}


/// ----------------------------------------------------------------------
/// \brief Envia una comanda TOGGLE al servei.
/// \param output: La sortida.
///
void DigOutputService::Implementation::toggle(
	DigOutput *output) {

	Command command;
    command.action = Action::toggle;
    command.outputImpl = output->getImpl();
    commandQueue.put(command, (unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief Envia una comanda PULSE al servei.
/// \param output: La sortida.
/// \param width: L'amplada del puls.
///
void DigOutputService::Implementation::pulse(
	DigOutput *output,
	uint16_t width) {

	Command command;
    command.action = Action::pulse;
    command.outputImpl = output->getImpl();
    command.width = width;
    commandQueue.put(command, (unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief Envia una comanda DELAYED PULSE al servei.
/// \param output: La sortida.
/// \param delay: El retart fins l'inici del puls.
/// \param width: L'amplada del puls.
///
void DigOutputService::Implementation::delayedPulse(
	DigOutput *output,
	uint16_t delay,
	uint16_t width) {

	Command command;
    command.action = Action::delayedPulse;
    command.outputImpl = output->getImpl();
    command.delay = delay;
    command.width = width;
    commandQueue.put(command, (unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza l'objecte.
/// \param info: Parametres d'inicialitzacio.
///
DigOutput::Implementation::Implementation(
	const DigOutputInitializeInfo *info):

	port(info->port),
	pin(info->pin),
	state(State::Done),
	timer(nullptr) {

    GPIOInitializePinInfo pinInfo;
    pinInfo.port = port;
    pinInfo.pin = pin;
    pinInfo.options =
        (info->openDrain ? HAL_GPIO_MODE_OUTPUT_OD : HAL_GPIO_MODE_OUTPUT_PP) |
        (info->initState ? HAL_GPIO_INIT_SET : HAL_GPIO_INIT_CLR);
    halGPIOInitializePins(&pinInfo, 1);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
DigOutput::Implementation::~Implementation() {

	if (timer != nullptr)
		delete timer;
}


/// ----------------------------------------------------------------------
/// \brief Obte el valor de la sortida.
/// \return El valor obtingut.
///
bool DigOutput::Implementation::get() const {

	return halGPIOReadPin(port, pin);
}


/// ----------------------------------------------------------------------
/// \brief Asigna una sortida al valor actiu.
///
void DigOutput::Implementation::set() {

	osalEnterCritical();

	if (state != State::Done)
    	stopTimer();

    halGPIOSetPin(port, pin);
    state = State::Done;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Asigna una sortida al valor no actiu.
///
void DigOutput::Implementation::clear() {

	osalEnterCritical();

	if (state != State::Done)
    	stopTimer();

    halGPIOClearPin(port, pin);
    state = State::Done;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Inverteix una sortida.
///
void DigOutput::Implementation::toggle() {

	osalEnterCritical();

	if (state != State::Done)
    	stopTimer();

    halGPIOTogglePin(port, pin);
    state = State::Done;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Genera un puls. Inverteix la sortida durant el temps especificad,
///        despres retorna al seu valor original.
/// \param width: Amplada del puls.
///
void DigOutput::Implementation::pulse(
	uint16_t width) {

	osalEnterCritical();

	if (state == State::Done)
        halGPIOTogglePin(port, pin);

    startTimer(width);
    state = State::Pulse;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Genera un puls retardat. Inverteix la sortida durant el temps
///        especificad, despres retorna al seu valor original.
/// \param delay: Retard fins l'inici del puls.
/// \param width: Amplada del puls.
///
void DigOutput::Implementation::delayedPulse(
	uint16_t delay,
	uint16_t width) {

	osalEnterCritical();

	startTimer(delay);
    time = width;
    state = State::Delay;

    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Posa en marxa el temporitzador.
/// \param time: El temps.
///
void DigOutput::Implementation::startTimer(
	uint16_t time) {

	if (timer == nullptr) {
		timer = new Timer();
		timer->setEvTimeout<Implementation>(this, &Implementation::onTimeout);
		timer->setTag(this);
	}
	timer->start(time, 0);
}


/// ----------------------------------------------------------------------
/// \brief Para el tempositzador.
///
void DigOutput::Implementation::stopTimer() {

	if (timer != nullptr)
		timer->stop((unsigned) -1);
}


/// ----------------------------------------------------------------------
/// \brief Motifica l'event timeout del temporitzador.
/// \param timer: El temporitzador que genera l'event.
///
void DigOutput::Implementation::onTimeout(
	Timer *timer) {

    osalEnterCritical();

    switch (state) {
    	case State::Done:
    		break;

    	case State::Pulse:
    	    halGPIOTogglePin(port, pin);
    	    stopTimer();
    		state = State::Done;
    		break;

    	case State::Delay:
    	    halGPIOTogglePin(port, pin);
    	    startTimer(time);
    		state = State::Pulse;
    		break;
    }

    osalExitCritical();
}

