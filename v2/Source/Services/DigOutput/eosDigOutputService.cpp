#include "eos.h"
#include "eosAssert.h"
#include "Services/eosDigOutputService.h"
#include "System/Core/eosTask.h"

#include <cmath>
#include <limits>

#include "HTL/htlINT.h"


namespace eos {
	class Output final: public DigOutput {
		public:
			enum class State {
				idle,
				pulse,
				delayedSet,
				delayedClear,
				delayedToggle,
				delayedPulse,
			};

		private:
			PinDriver * const _drv;
			bool _value;
			State _state;
			unsigned _delayEndTime;
			unsigned _pulseEndTime;

		private:
			static bool hasExpired(unsigned time, unsigned endTime);

		public:
			Output(PinDriver *drv);
			bool getValue() const;
			void set();
			void clear();
			void toggle();
			void pulse(unsigned time, unsigned pulse);
			void delayedSet(unsigned time, unsigned delay);
			void delayedClear(unsigned time, unsigned delay);
			void delayedToggle(unsigned time, unsigned delay);
			void delayedPulse(unsigned time, unsigned delay, unsigned pulse);
			void write(bool value);
			void tick(unsigned time);
	};
}


using namespace eos;
using namespace htl;
using namespace htl::irq;


constexpr const char *serviceName = "DigOutputs";
constexpr Task::Priority servicePriority = Task::Priority::normal;
constexpr unsigned serviceStackSize = 164;

constexpr unsigned minPulseWidth = DigOutputService_MinPulseWidth;
constexpr unsigned minDelay = DigOutputService_MinDelay;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
DigOutputService::DigOutputService():
	_timeCounter {0},
	_commandQueue {_commandQueueSize} {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

	removeOutputs();
}


/// ----------------------------------------------------------------------
/// \brief    Crea una una sortida.
/// \param    pinDrv: El driver del pin
/// \return   La sortida.
///
DigOutput* DigOutputService::makeOutput(
    PinDriver *drv) {

    eosAssert(drv != nullptr);

    return new Output(drv);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una sortida al servei.
/// \param    output: La sortida a afeigir.
///
void DigOutputService::addOutput(
    DigOutput *output) {

    eosAssert(output != nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    // Afegeix la sortida a la llista
    //
    if (!_outputs.contains(output))
		_outputs.pushFront(output);

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una sortida del servei.
/// \param    output: La sortida a eliminar.
/// \remarks  Nomes es poden eliminar sortides, quan el servei no
///           esta inicialitzat.
///
void DigOutputService::removeOutput(
    DigOutput *output) {

    eosAssert(output != nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    // Elimina la sortida de la llista
    //
    if (_outputs.contains(output))
        _outputs.remove(output);

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les sortides del servei.
/// \remarks  Nomes es poden eliminar sortides, quan el servei
///           no esta inicialitzat.
///
void DigOutputService::removeOutputs() {

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    // Elimina totes les entrades de la llista
    //

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Notifica un canvi en l'estat d'una sortida.
/// \param    output: La sortida.
///
void DigOutputService::raiseChangedNotification(
	Output *output) {

	if (_erNotification.isEnabled()) {

    	NotificationEventArgs args = {
			.id {NotificationID::changed},
			.changed {
				.output {output},
				.value {output->getValue()}
			}
		};

		_erNotification(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat ACTIU.
/// \param    output: La sortida.
///
void DigOutputService::set(
    DigOutput *output) {

    eosAssert(output != nullptr);

    Command command = {
        .id {CommandID::set},
        .output {static_cast<Output*>(output)}
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat IDLE.
/// \param    output: La sortida.
///
void DigOutputService::clear(
    DigOutput *output) {

    eosAssert(output != nullptr);

    Command command = {
        .id {CommandID::clear},
        .output {static_cast<Output*>(output)}
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat de la sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggle(
    DigOutput *output) {

    eosAssert(output != nullptr);

    Command command = {
        .id {CommandID::toggle},
        .output {static_cast<Output*>(output)}
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'estat de la sortida.
/// \param    output: La sortida.
/// \param    state: L'estat a asignar.
///
void DigOutputService::write(
    DigOutput *output,
    bool state) {

    eosAssert(output != nullptr);

    Command command = {
        .id {state ? CommandID::set : CommandID::clear},
        .output {static_cast<Output*>(output)}
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio.
/// \param    output: La sortida.
/// \param    width: L'amplada del puls.
///
void DigOutputService::pulse(
    DigOutput *output,
    unsigned width) {

    eosAssert(output != nullptr);

    Command command = {
        .id {CommandID::pulse},
        .output {static_cast<Output*>(output)},
        .time1 {std::max(width, minPulseWidth)}
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio retardat.
/// \param    output: La sortida.
/// \param    delay: El retard del puls.
/// \param    width: L'amplada del puls.
///
void DigOutputService::delayedPulse(
    DigOutput *output,
    unsigned delay,
    unsigned width) {

    eosAssert(output != nullptr);

    Command command = {
        .id {CommandID::delayedPulse},
        .output {static_cast<Output*>(output)},
        .time1 {std::max(delay, minDelay)},
        .time2 {std::max(width, minPulseWidth)}
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el valor d'una sortida.
/// \param    output: La sortida.
/// \return   L'estat de la sortida.
///
bool DigOutputService::read(
	DigOutput *output) {

    eosAssert(output != nullptr);

    auto s = getInterruptState();
    if (s)
    	disableInterrupts();

    auto out = static_cast<Output*>(output);
    bool value = out->getValue();

    if (s)
    	enableInterrupts();

    return value;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
/// \param    params: Els parametres.
///
void DigOutputService::onInitialize(
	ServiceParams &params) {

	params.name = serviceName;
	params.stackSize = serviceStackSize;
	params.priority = servicePriority;
}


/// ----------------------------------------------------------------------
/// \brief    Tasca del servei.
///
void DigOutputService::onExecute() {

	while (!stopSignal()) {
		Command command;
		while (_commandQueue.pop(command, (unsigned) -1))
			commandDispatcher(command);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les comandes.
/// \param    command: La comanda.
///
void DigOutputService::commandDispatcher(
	const Command &command) {

    switch (command.id) {
        case CommandID::set:
            processSet(command.output);
            break;

        case CommandID::clear:
            processClear(command.output);
            break;

        case CommandID::toggle:
            processToggle(command.output);
            break;

        case CommandID::pulse:
            processPulse(command.output, command.time1);
            break;

        case CommandID::delayedSet:
            processDelayedSet(command.output, command.time1);
            break;

        case CommandID::delayedClear:
            processDelayedClear(command.output, command.time1);
            break;

        case CommandID::delayedToggle:
            processDelayedToggle(command.output, command.time1);
            break;

        case CommandID::delayedPulse:
            processDelayedPulse(command.output, command.time1, command.time2);
            break;

        case CommandID::tick:
            processTick();
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'clear'
/// \param    output: La sortida.
///
void DigOutputService::processClear(
    Output *output) {

	if (output->getValue()) {
		output->clear();
		raiseChangedNotification(output);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'set'
/// \param    output: La sortida.
///
void DigOutputService::processSet(
    Output *output) {

	if (!output->getValue()) {
		output->set();
		raiseChangedNotification(output);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    output: La sortida.
///
void DigOutputService::processToggle(
    Output *output) {

	output->toggle();
	raiseChangedNotification(output);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'pulse'.
/// \param    output: La sortida.
/// \param    pulseWidth: L'amplada del puls.
///
void DigOutputService::processPulse(
    Output *output,
    unsigned pulseWidth) {

	bool oldValue = output->getValue();
	output->pulse(_timeCounter, pulseWidth);
	if (oldValue != output->getValue())
		raiseChangedNotification(output);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedSet'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::processDelayedSet(
    Output *output,
    unsigned delay) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedClear'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::processDelayedClear(
    Output *output,
    unsigned delay) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedToggle'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::processDelayedToggle(
    Output *output,
    unsigned delay) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedPulse'.
/// \param    output: La sortida.
/// \param    delay: El retard del puls.
/// \param    pulseWidth: L'amplada del puls.
///
void DigOutputService::processDelayedPulse(
    Output *output,
    unsigned delay,
    unsigned pulseWidth) {

	output->delayedPulse(_timeCounter, delay, pulseWidth);
}


/// ---------------------------------------------------------------------
/// \brief    Procesa la comanda 'tick'
///
void DigOutputService::processTick() {

	for (auto o: _outputs) {
    	auto output = static_cast<Output*>(o);

    	bool oldValue = output->getValue();
		output->tick(_timeCounter);
		if (oldValue != output->getValue())
			raiseChangedNotification(output);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temportitzador
/// \remarks  ATENCIO: Es procesa dins d'una interrupcio.
///
void DigOutputService::tickISR() {

	// Incrementa el contador de temps
	//
	_timeCounter += 1;

    Command command = {
        .id {CommandID::tick}
    };

    // Es porta el missatge en la cua, per procesar-l'ho en la tasca,
    // fora de la interrupcio.
    //
    _commandQueue.pushISR(command);
}


/// ----------------------------------------------------------------------
/// \brief    Contructor
/// \param    dev: El driver del pin.
///
Output::Output(
	PinDriver *drv):

	_drv {drv},
	_value {drv->read()},
	_state{State::idle} {
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor actual de la sortida.
/// \return   El valor.
///
bool Output::getValue() const {

	return _value;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un nou valor en la sortida.
/// \param    value: El nou valor.
///
void Output::write(
	bool value) {

	_value = value;
	_drv->write(value);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu el valor true en la sortida.
///
void Output::set() {

	write(true);
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu el valor false en la sortida.
///
void Output::clear() {

	write(false);
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix el valor de la sortida.
///
void Output::toggle() {

	write(!_value);
	_state = State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls en la sortida.
/// \param    time: El temps actual.
/// \param    pulse: Durada del puls.
///
void Output::pulse(
	unsigned time,
	unsigned pulse) {

	if (_state == State::idle)
		write(!_value);

	_pulseEndTime = time + pulse;
	_state = State::pulse;
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida al valor true despres d'un retard.
/// \param    time: El temps actual.
/// \param    delay: Durada del retard.
///
void Output::delayedSet(
	unsigned time,
	unsigned delay) {

	_delayEndTime = time + delay;
	_state = State::delayedSet;
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida al valor false despres d'un retard.
/// \param    time: El temps actual.
/// \param    delay: Durada del retard.
///
void Output::delayedClear(
	unsigned time,
	unsigned delay) {

	_delayEndTime = time + delay;
	_state = State::delayedClear;
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix el valor despres d'un retard.
/// \param    time: El temps actual.
/// \param    delay: Durada del retard.
///
void Output::delayedToggle(
	unsigned time,
	unsigned delay) {

	_delayEndTime = time + delay;
	_state = State::delayedToggle;
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls retardat en la sortida.
/// \param    time: El temps actual.
/// \brief    delay: Durada del retard.
/// \param    pulse: Durada del puls.
///
void Output::delayedPulse(
	unsigned time,
	unsigned delay,
	unsigned pulse) {

	_delayEndTime = time + delay;
	_pulseEndTime = time + delay + pulse;
	_state = State::delayedPulse;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa els temps.
/// \param    time: El temps actual.
///
void Output::tick(
	unsigned time) {

	switch (_state) {
		case State::pulse:
			if (hasExpired(time, _pulseEndTime)) {
				write(!_value);
				_state = State::idle;
			}
			break;

		case State::delayedSet:
			if (hasExpired(time, _delayEndTime)) {
				write(true);
				_state = State::idle;
			}
			break;

		case State::delayedClear:
			if (hasExpired(time, _delayEndTime)) {
				write(false);
				_state = State::idle;
			}
			break;

		case State::delayedToggle:
			if (hasExpired(time, _delayEndTime)) {
				write(!_value);
				_state = State::idle;
			}
			break;

		case State::delayedPulse:
			if (hasExpired(time, _delayEndTime)) {
				write(!_value);
				_state = State::pulse;
			}
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si el temps ha expirat.
/// \param    time: Temp actual.
/// \param    endTime: Temps limit.
/// \return   True si el temps actual es posterior al temps limit.
///
bool Output::hasExpired(
	unsigned time,
	unsigned endTime) {

	auto delta = endTime - time;
	return static_cast<int>(delta) <= 0;
}
