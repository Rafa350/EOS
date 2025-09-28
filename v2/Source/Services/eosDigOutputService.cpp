#include "eos.h"
#include "eosAssert.h"
#include "Services/eosDigOutputService.h"
#include "System/Core/eosTask.h"

#include <cmath>
#include <limits>


#ifdef HTL_MODULAR
import htl.interrupts;
#else
#include "HTL/htlINT.h"
namespace interrupts = htl::irq;
#endif


using namespace eos;
using namespace htl;


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
/// \param    drv: El driver del pin
/// \return   La sortida afeigida.
///
IDigOutput* DigOutputService::makeOutput(
    PinDriver *drv) {

    eosAssert(drv != nullptr);

    auto output = new DigOutput(drv);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una sortida al servei.
/// \param    output: La sortida a afeigir.
///
void DigOutputService::addOutput(
    IDigOutput *output) {

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
    IDigOutput *output) {

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
	IDigOutput *output) {

	if (_erNotify.isEnabled(NotifyID::changed)) {
		NotifyEventArgs args = {
			.changed = {
				.output = output
			}
		};
		_erNotify.raise(NotifyID::changed, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza el proper temps limit
/// \return   El resultat.
///
void DigOutputService::updateNextTimeLimit() {

    unsigned timeLimit = std::numeric_limits<unsigned>::max();

    for (auto output: _outputs) {
    	auto o = static_cast<DigOutput*>(output);
        if ((o->_state != DigOutput::State::idle) &&
            (o->_timeLimit < timeLimit))
            timeLimit = o->_timeLimit;
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
	IDigOutput *output) {

	auto o = static_cast<DigOutput*>(output);

	auto drv = o->_drv;
    if (drv->read() == false) {
    	drv->set();
    	notifyChanged(o);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Posa l'estat d'una sortida clr.
/// \param    output: La sortida.
///
void DigOutputService::clearOutput(
	IDigOutput *output) {

	auto o = static_cast<DigOutput*>(output);

	auto drv = o->_drv;
	if (drv->read() == true) {
    	drv->clear();
    	notifyChanged(o);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat d'una sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggleOutput(
	IDigOutput *output) {

	auto o = static_cast<DigOutput*>(output);

	auto drv = o->_drv;
	drv->toggle();
   	notifyChanged(o);
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat ACTIU.
/// \param    output: La sortida.
///
void DigOutputService::set(
    IDigOutput *output) {

    eosAssert(output != nullptr);

    Command command = {
        .id = CommandID::set,
        .output = output
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat IDLE.
/// \param    output: La sortida.
///
void DigOutputService::clear(
    IDigOutput *output) {

    eosAssert(output != nullptr);

    Command command = {
        .id = CommandID::clear,
        .output = output
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat de la sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggle(
    IDigOutput *output) {

    eosAssert(output != nullptr);

    Command command = {
        .id = CommandID::toggle,
        .output = output
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'estat de la sortida.
/// \param    output: La sortida.
/// \param    state: L'estat a asignar.
///
void DigOutputService::write(
    IDigOutput *output,
    bool state) {

    eosAssert(output != nullptr);

    Command command = {
        .id = state ? CommandID::set : CommandID::clear,
        .output = output
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio.
/// \param    output: La sortida.
/// \param    width: L'amplada del puls.
///
void DigOutputService::pulse(
    IDigOutput *output,
    unsigned width) {

    eosAssert(output != nullptr);

    Command command = {
        .id = CommandID::pulse,
        .output = output,
        .time1 = std::max(width, minPulseWidth)
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
    IDigOutput *output,
    unsigned delay,
    unsigned width) {

    eosAssert(output != nullptr);

    Command command = {
        .id = CommandID::delayedPulse,
        .output = output,
        .time1 = std::max(delay, minDelay),
        .time2 = std::max(width, minPulseWidth)
    };

    _commandQueue.push(command, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix l'estat actual d'una sortida.
/// \param    output: La sortida.
/// \return   L'estat de la sortida.
///
bool DigOutputService::read(
	IDigOutput *output) {

    eosAssert(output != nullptr);

    auto o = static_cast<DigOutput*>(output);

    interrupts::disableInterrupts();
    bool pinState = o->_drv->read();
    interrupts::enableInterrupts();

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
    IDigOutput *output) {

    eosAssert(output != nullptr);

    auto o = static_cast<DigOutput*>(output);

    clearOutput(o);
   	o->_state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'set'
/// \param    output: La sortida.
///
void DigOutputService::processSet(
    IDigOutput *output) {

    eosAssert(output != nullptr);

	auto o = static_cast<DigOutput*>(output);

	setOutput(o);
   	o->_state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    output: La sortida.
///
void DigOutputService::processToggle(
    IDigOutput *output) {

    eosAssert(output != nullptr);

    auto o = static_cast<DigOutput*>(output);

    toggleOutput(o);
    o->_state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'pulse'.
/// \param    output: La sortida.
/// \param    pulseWidth: L'amplada del puls.
///
void DigOutputService::processPulse(
    IDigOutput *output,
    unsigned pulseWidth) {

    eosAssert(output != nullptr);

    auto o = static_cast<DigOutput*>(output);

    if (o->_state == DigOutput::State::idle)
    	toggleOutput(o);
    o->_state = DigOutput::State::pulse;
    o->_timeLimit = _timeCounter + pulseWidth;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedSet'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::processDelayedSet(
    IDigOutput *output,
    unsigned delay) {

    eosAssert(output != nullptr);

	auto o = static_cast<DigOutput*>(output);

	o->_state = DigOutput::State::delayedSet;
    o->_timeLimit = _timeCounter + delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedClear'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::processDelayedClear(
    IDigOutput *output,
    unsigned delay) {

    eosAssert(output != nullptr);

    auto o = static_cast<DigOutput*>(output);

    o->_state = DigOutput::State::delayedClear;
    o->_timeLimit = _timeCounter + delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedToggle'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void DigOutputService::processDelayedToggle(
    IDigOutput *output,
    unsigned delay) {

    eosAssert(output != nullptr);

	auto o = static_cast<DigOutput*>(output);

	o->_state = DigOutput::State::delayedToggle;
    o->_timeLimit = _timeCounter + delay;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedPulse'.
/// \param    output: La sortida.
/// \param    delay: El retard del puls.
/// \param    pulseWidth: L'amplada del puls.
///
void DigOutputService::processDelayedPulse(
    IDigOutput *output,
    unsigned delay,
    unsigned pulseWidth) {

    eosAssert(output != nullptr);

	auto o = static_cast<DigOutput*>(output);

    o->_state = DigOutput::State::delayedPulse;
    auto tc = _timeCounter;
    o->_timeLimit = tc + delay;
    o->_timeLimit2 = tc + delay + pulseWidth;
}


/// ---------------------------------------------------------------------
/// \brief    Procesa la comanda 'tick'
///
void DigOutputService::processTick() {

    for (auto output: _outputs) {
    	auto o = static_cast<DigOutput*>(output);
		if (hasExpired(o->_timeLimit))
			switch (o->_state) {
				case DigOutput::State::pulse:
					toggleOutput(o);
					o->_state = DigOutput::State::idle;
					break;

				case DigOutput::State::delayedSet:
					setOutput(o);
					o->_state = DigOutput::State::idle;
					break;

				case DigOutput::State::delayedClear:
					clearOutput(o);
					o->_state = DigOutput::State::idle;
					break;

				case DigOutput::State::delayedToggle:
					toggleOutput(o);
					o->_state = DigOutput::State::idle;
					break;

				case DigOutput::State::delayedPulse:
					toggleOutput(o);
					o->_timeLimit = o->_timeLimit2;
					o->_state = DigOutput::State::pulse;
					break;

				default:
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
        .id = CommandID::tick
    };

    // Es porta el missatge en la cua, per procesar-l'ho en la tasca,
    // fora de la interrupcio.
    //
    _commandQueue.pushISR(command);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    drv: El driver del pin
///
DigOutput::DigOutput(
    PinDriver *drv):

    _drv {drv},
    _state {State::idle} {
}
