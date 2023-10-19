#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlINT.h"
#include "Services/eosDigOutputService.h"
#include "System/eosMath.h"
#include "System/Core/eosTask.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
DigOutputService::DigOutputService():
	_changedEvent {nullptr},
	_changedEventEnabled {false},
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
/// \brief    Afegeig una sortida al servei.
/// \param    output: La sortida a afeigir.
/// \remarks  Nomes es poden afeigir sortides, quan el servei no
///           esta inicialitzat.
///
void DigOutputService::addOutput(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == nullptr);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (output->_service == nullptr) {
        _outputs.pushBack(output);
        output->_service = this;
    }

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
    eosAssert(output->_service == this);

    // Inici de seccio critica. No es pot permetre accedir durant els canvis
    //
    Task::enterCriticalSection();

    if (output->_service == this) {
        _outputs.remove(output);
        output->_service = nullptr;
    }

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

    while (!_outputs.isEmpty()) {
        DigOutput *output = _outputs.peekFront();
        _outputs.remove(output);
        output->_service = nullptr;
    }

    // Fi de la seccio critica
    //
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el event 'Changed'
/// \param    event: El event.
/// \param    enabled: True per habilitar.
///
void DigOutputService::setChangedEvent(
	IChangedEvent &event,
	bool enabled) {

	_changedEvent = &event;
	_changedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'Changed'
///
void DigOutputService::enableChangedEvent() {

	_changedEventEnabled = _changedEvent != nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita l'event 'Changed'
///
void DigOutputService::disableChangedEvent() {

	_changedEventEnabled = false;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica un canvi en l'estat d'una sortida.
/// \param    output: La sortida.
///
void DigOutputService::notifyChanged(
	DigOutput *output) {

	if (_changedEventEnabled) {
		ChangedEventArgs args = {
			.output = output
		};
		_changedEvent->execute(this, args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Coproca si ha expirat el temps.
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

	auto drv = output->_drv;
    if (drv->read() == false) {
    	drv->set();
    	notifyChanged(output);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Posa l'estat d'una sortida clr.
/// \param    output: La sortida.
///
void DigOutputService::clearOutput(
	DigOutput *output) {

	auto drv = output->_drv;
	if (drv->read() == true) {
    	drv->clear();
    	notifyChanged(output);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat d'una sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggleOutput(
	DigOutput *output) {

	auto drv = output->_drv;
	drv->toggle();
   	notifyChanged(output);
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat ON.
/// \param    output: La sortida.
///
void DigOutputService::set(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .id = CommandID::set,
        .output = output
    };

    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat OFF.
/// \param    output: La sortida.
///
void DigOutputService::clear(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .id = CommandID::clear,
        .output = output
    };

    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat de la sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggle(
    DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .id = CommandID::toggle,
        .output = output
    };

    _commandQueue.push(cmd, unsigned(-1));
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
    eosAssert(output->_service == this);

    Command cmd = {
        .id = state ? CommandID::set : CommandID::clear,
        .output = output
    };

    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio.
/// \param    output: La sortida.
/// \param    pulseWidth: L'amplada del puls.
///
void DigOutputService::pulse(
    DigOutput *output,
    unsigned pulseWidth) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .id = CommandID::pulse,
        .output = output,
        .time1 = math::max(pulseWidth, minPulseWidth)
    };

    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio retardat.
/// \param    output: La sortida.
/// \param    delay: El retard del puls.
/// \param    pulseWidth: L'amplada del puls.
///
void DigOutputService::delayedPulse(
    DigOutput *output,
    unsigned delay,
    unsigned pulseWidth) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .id = CommandID::delayedPulse,
        .output = output,
        .time1 = math::max(delay, minDelay),
        .time2 = math::max(pulseWidth, minPulseWidth)
    };

    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix l'estat actual d'una sortida.
/// \param    output: La sortida.
/// \return   L'estat de la sortida.
///
bool DigOutputService::read(
	DigOutput *output) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    bool saveIrq = irq::disableInterrupts();
    bool pinState = output->_drv->read();
    irq::restoreInterrupts(saveIrq);

    return pinState;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void DigOutputService::onInitialize() {

    // Inicialitza el servei base.
    //
    Service::onInitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Bucle de proces del servei.
///
void DigOutputService::onTask() {

    while (true) {
        Command command;
        while (_commandQueue.pop(command, unsigned(-1)))
        	processCommand(command);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio 'tick'.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
#if Eos_ApplicationTickEnabled
void DigOutputService::onTick() {

}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa una comanda.
/// \param    command: La comanda.
///
void DigOutputService::processCommand(
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

    clearOutput(output);
   	output->_state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'set'
/// \param    output: La sortida.
///
void DigOutputService::processSet(
    DigOutput *output) {

    eosAssert(output != nullptr);

    setOutput(output);
   	output->_state = DigOutput::State::idle;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    output: La sortida.
///
void DigOutputService::processToggle(
    DigOutput *output) {

    eosAssert(output != nullptr);

    toggleOutput(output);
    output->_state = DigOutput::State::idle;
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

    if (output->_state == DigOutput::State::idle)
    	toggleOutput(output);
    output->_state = DigOutput::State::pulse;
    output->_timeLimit = _timeCounter + pulseWidth;
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

    output->_state = DigOutput::State::delayedSet;
    output->_timeLimit = _timeCounter + delay;
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

    output->_state = DigOutput::State::delayedClear;
    output->_timeLimit = _timeCounter + delay;
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

    output->_state = DigOutput::State::delayedToggle;
    output->_timeLimit = _timeCounter + delay;
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

    output->_state = DigOutput::State::delayedPulse;
    auto tc = _timeCounter;
    output->_timeLimit = tc + delay;
    output->_timeLimit2 = tc + delay + pulseWidth;
}


/// ---------------------------------------------------------------------
/// \brief    Procesa la comanda 'tick'
///
void DigOutputService::processTick() {

    for (auto output: _outputs) {
		if (hasExpired(output->_timeLimit))
			switch (output->_state) {
				case DigOutput::State::pulse:
					toggleOutput(output);
					output->_state = DigOutput::State::idle;
					break;

				case DigOutput::State::delayedSet:
					setOutput(output);
					output->_state = DigOutput::State::idle;
					break;

				case DigOutput::State::delayedClear:
					clearOutput(output);
					output->_state = DigOutput::State::idle;
					break;

				case DigOutput::State::delayedToggle:
					toggleOutput(output);
					output->_state = DigOutput::State::idle;
					break;

				case DigOutput::State::delayedPulse:
					toggleOutput(output);
					output->_timeLimit = output->_timeLimit2;
					output->_state = DigOutput::State::pulse;
					break;
			}
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temportitzador
/// \param    event: L'event que ha generat la interrupcio.
/// \remarks  ATENCIO: Es procesa d'ins d'una interrupcio.
///
void DigOutputService::tmrInterruptFunction() {

	// Incrementa el contador de temps
	//
	_timeCounter++;

    Command cmd = {
        .id = CommandID::tick
    };

    _commandQueue.pushISR(cmd);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    service: El servei al que s'asignara la sortida.
/// \param    drv: El driver del pin
///
DigOutput::DigOutput(
    DigOutputService *service,
    PinDriver *drv):

    _service {nullptr},
    _drv {drv},
    _state {State::idle} {

    if (service != nullptr)
        service->addOutput(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
DigOutput::~DigOutput() {

    if (_service != nullptr)
        _service->removeOutput(this);
}
