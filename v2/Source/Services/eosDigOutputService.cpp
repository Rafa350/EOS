#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlINT.h"
#include "Services/eosDigOutputService.h"
#include "System/Core/eosTask.h"

#include <cmath>
#include <limits>


using namespace eos;
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

    // Afegeix la sortida a la llista
    //
    if (output->_service == nullptr) {
        output->_service = this;
        _outputs.pushFront(output);
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

    // Elimina la sortida de la llista
    //
    if (output->_service == this) {
        output->_service = nullptr;
        _outputs.remove(output);
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

    // Elimina totes les entrades de la llista
    //
    /*auto c = _first;
    while (c != nullptr) {
        auto output = c;

        c = c->_next;

        output->_next = nullptr;
        output->_service = nullptr;
    }*/


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

	if (_evRaiser.isEnabled(NotifyId::changed)) {
		NotifyEventArgs args = {
			.service = this,
			.id = NotifyId::changed,
			.changed = {
				.output = output,
				.pinState = output->read()
			}
		};
		_evRaiser.raise(NotifyId::changed, args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza el proper temps limit
/// \return   El resultat.
///
void DigOutputService::updateNextTimeLimit() {

    unsigned timeLimit = std::numeric_limits<unsigned>::max();

    for (auto output: _outputs) {
        if ((output->_state != DigOutput::State::idle) &&
            (output->_timeLimit < timeLimit))
            timeLimit = output->_timeLimit;
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
        .id = CommandId::set,
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
        .id = CommandId::clear,
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
        .id = CommandId::toggle,
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
        .id = state ? CommandId::set : CommandId::clear,
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
        .id = CommandId::pulse,
        .output = output,
        .time1 = std::max(pulseWidth, minPulseWidth)
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
        .id = CommandId::delayedPulse,
        .output = output,
        .time1 = std::max(delay, minDelay),
        .time2 = std::max(pulseWidth, minPulseWidth)
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

    disableInterrupts();
    bool pinState = output->_drv->read();
    enableInterrupts();

    return pinState;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
/// \param    params: Els parametres.
///
void DigOutputService::initService(
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
        case CommandId::set:
            processSet(command.output);
            break;

        case CommandId::clear:
            processClear(command.output);
            break;

        case CommandId::toggle:
            processToggle(command.output);
            break;

        case CommandId::pulse:
            processPulse(command.output, command.time1);
            break;

        case CommandId::delayedSet:
            processDelayedSet(command.output, command.time1);
            break;

        case CommandId::delayedClear:
            processDelayedClear(command.output, command.time1);
            break;

        case CommandId::delayedToggle:
            processDelayedToggle(command.output, command.time1);
            break;

        case CommandId::delayedPulse:
            processDelayedPulse(command.output, command.time1, command.time2);
            break;

        case CommandId::tick:
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

				default:
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
        .id = CommandId::tick
    };

    // Es porta el missatge en la cua, per procesar-l'ho en la tasca,
    // fora de la interrupcio.
    //
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
