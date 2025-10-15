#include "eos.h"
#include "eosAssert.h"
#include "Services/eosDigOutputService.h"
#include "System/Core/eosTask.h"

#include <cmath>
#include <limits>

#include "HTL/htlINT.h"


namespace eos {

    class Output final: public DigOutput {

    	public: enum class State {
			idle,
			pulse,
			delayedSet,
			delayedClear,
			delayedToggle,
			delayedPulse,
		};

        public: PinDriver * const drv;
        public: State state;
        public: unsigned timeLimit;
        public: unsigned timeLimit2;

        public: Output(PinDriver *pinDrv):
			drv {pinDrv},
			state{State::idle} {
		}
    };
}


using namespace eos;
using namespace htl;
using namespace htl::irq;


constexpr const char *serviceName = "DigOutput";
constexpr Task::Priority servicePriority = Task::Priority::normal;
constexpr unsigned serviceStackSize = 128;

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
    PinDriver *pinDrv) {

    eosAssert(pinDrv != nullptr);

    return new Output(pinDrv);
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
void DigOutputService::notifyChanged(
	DigOutput *output) {

    eosAssert(output != nullptr);

	if (_erNotify.isEnabled()) {

		NotifyEventArgs args = {
			.id {NotifyID::changed},
			.changed {
				.output {output}
			}
		};

		_erNotify(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza el proper temps limit
/// \return   El resultat.
///
void DigOutputService::updateNextTimeLimit() {

    unsigned timeLimit = std::numeric_limits<unsigned>::max();

    for (auto output: _outputs) {
    	auto out = static_cast<Output*>(output);
        if ((out->state != Output::State::idle) &&
            (out->timeLimit < timeLimit))
            timeLimit = out->timeLimit;
    }

    if (timeLimit < std::numeric_limits<unsigned>::max())
        _nextTimeLimit = timeLimit;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si ha expirat el temps.
/// \param    timeLimit: El temps limit.
/// \return   True si ha sobrepasat el temps.
///
bool DigOutputService::hasExpired(
    unsigned timeLimit) const {

    auto delta = timeLimit - _timeCounter;
    return static_cast<int>(delta) <= 0;
}


/// ----------------------------------------------------------------------
/// \brief    Posa l'estat d'una sortida set.
/// \param    output: La sortida.
///
void DigOutputService::setOutput(
	DigOutput *output) {

    eosAssert(output != nullptr);

    auto out = static_cast<Output*>(output);

	auto drv = out->drv;
    if (drv->read() == false) {
    	drv->set();
    	notifyChanged(out);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Posa l'estat d'una sortida clr.
/// \param    output: La sortida.
///
void DigOutputService::clearOutput(
	DigOutput *output) {

    eosAssert(output != nullptr);

    auto out = static_cast<Output*>(output);

	auto drv = out->drv;
	if (drv->read() == true) {
    	drv->clear();
    	notifyChanged(out);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat d'una sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggleOutput(
	DigOutput *output) {

    eosAssert(output != nullptr);

    auto out = static_cast<Output*>(output);

	auto drv = out->drv;
	drv->toggle();
   	notifyChanged(out);
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
        .output {output}
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
        .output {output}
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
        .output {output}
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
        .output {output}
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
        .output {output},
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
        .output {output},
        .time1 {std::max(delay, minDelay)},
        .time2 {std::max(width, minPulseWidth)}
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix l'estat actual d'una sortida.
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
    bool pinState = out->drv->read();

    if (s)
    	enableInterrupts();

    return pinState;
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
    DigOutput *output) {

    eosAssert(output != nullptr);

    auto out = static_cast<Output*>(output);

    clearOutput(out);
   	out->state = Output::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'set'
/// \param    output: La sortida.
///
void DigOutputService::processSet(
    DigOutput *output) {

    eosAssert(output != nullptr);

	auto out = static_cast<Output*>(output);

	setOutput(out);
   	out->state = Output::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    output: La sortida.
///
void DigOutputService::processToggle(
    DigOutput *output) {

    eosAssert(output != nullptr);

    auto out = static_cast<Output*>(output);

    toggleOutput(out);
    out->state = Output::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'pulse'.
/// \param    output: La sortida.
/// \param    pulseWidth: L'amplada del puls.
///
void DigOutputService::processPulse(
    DigOutput *output,
    unsigned pulseWidth) {

    eosAssert(output != nullptr);

    auto out = static_cast<Output*>(output);

    if (out->state == Output::State::idle)
    	toggleOutput(out);
    out->state = Output::State::pulse;
    out->timeLimit = _timeCounter + pulseWidth;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedSet'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::processDelayedSet(
    DigOutput *output,
    unsigned delay) {

    eosAssert(output != nullptr);

	auto out = static_cast<Output*>(output);

	out->state = Output::State::delayedSet;
    out->timeLimit = _timeCounter + delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedClear'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::processDelayedClear(
    DigOutput *output,
    unsigned delay) {

    eosAssert(output != nullptr);

    auto out = static_cast<Output*>(output);

    out->state = Output::State::delayedClear;
    out->timeLimit = _timeCounter + delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedToggle'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::processDelayedToggle(
    DigOutput *output,
    unsigned delay) {

    eosAssert(output != nullptr);

	auto out = static_cast<Output*>(output);

	out->state = Output::State::delayedToggle;
    out->timeLimit = _timeCounter + delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedPulse'.
/// \param    output: La sortida.
/// \param    delay: El retard del puls.
/// \param    pulseWidth: L'amplada del puls.
///
void DigOutputService::processDelayedPulse(
    DigOutput *output,
    unsigned delay,
    unsigned pulseWidth) {

    eosAssert(output != nullptr);

	auto out = static_cast<Output*>(output);

    out->state = Output::State::delayedPulse;
    auto tc = _timeCounter;
    out->timeLimit = tc + delay;
    out->timeLimit2 = tc + delay + pulseWidth;
}


/// ---------------------------------------------------------------------
/// \brief    Procesa la comanda 'tick'
///
void DigOutputService::processTick() {

    for (auto output: _outputs) {
    	auto out = static_cast<Output*>(output);
		if (hasExpired(out->timeLimit))
			switch (out->state) {
				case Output::State::idle:
					break;

				case Output::State::pulse:
					toggleOutput(out);
					out->state = Output::State::idle;
					break;

				case Output::State::delayedSet:
					setOutput(out);
					out->state = Output::State::idle;
					break;

				case Output::State::delayedClear:
					clearOutput(out);
					out->state = Output::State::idle;
					break;

				case Output::State::delayedToggle:
					toggleOutput(out);
					out->state = Output::State::idle;
					break;

				case Output::State::delayedPulse:
					toggleOutput(out);
					out->timeLimit = out->timeLimit2;
					out->state = Output::State::pulse;
					break;
			}
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
