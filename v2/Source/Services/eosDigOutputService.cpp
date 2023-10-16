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
	_outputChangedEvent {nullptr},
	_outputChangedEventEnabled {false},
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
/// \param    enabled: True si esta habilitat.
///
void DigOutputService::setOutputChangedEvent(
	IOutputChangedEvent &event,
	bool enabled) {

	_outputChangedEvent = &event;
	_outputChangedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica un canvi en l'estat d'una sortida.
/// \param    output: La sortida.
///
void DigOutputService::notifyChanged(
	DigOutput *output) {

	if (_outputChangedEventEnabled) {
		OutputChangedEventArgs args = {
			.output = output
		};
		_outputChangedEvent->execute(this, args);
	}
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
        .opCode = OpCode::set,
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
        .opCode = OpCode::clear,
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
        .opCode = OpCode::toggle,
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
        .opCode = state ? OpCode::set : OpCode::clear,
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
        .opCode = OpCode::pulse,
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
        .opCode = OpCode::delayedPulse,
        .output = output,
        .time1 = math::max(delay, minDelay),
        .time2 = math::max(pulseWidth, minPulseWidth)
    };

    _commandQueue.push(cmd, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio ciclic.
/// \param    output: La sortida.
/// \param    pulseWidth: L'amplada del puls.
/// \param    spaceWidth: L'amplada del espai. 
///
void DigOutputService::repeatPulse(
    DigOutput *output,
    unsigned pulseWidth,
    unsigned spaceWidth) {

    eosAssert(output != nullptr);
    eosAssert(output->_service == this);

    Command cmd = {
        .opCode = OpCode::repeatPulse,
        .output = output,
        .time1 = math::max(pulseWidth, minPulseWidth),
        .time2 = math::max(spaceWidth, minPulseWidth)
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

    switch (command.opCode) {
        case OpCode::set:
            processSet(command.output);
            break;

        case OpCode::clear:
            processClear(command.output);
            break;

        case OpCode::toggle:
            processToggle(command.output);
            break;

        case OpCode::pulse:
            processPulse(command.output, command.time1);
            break;

        case OpCode::delayedSet:
            processDelayedSet(command.output, command.time1);
            break;

        case OpCode::delayedClear:
            processDelayedClear(command.output, command.time1);
            break;

        case OpCode::delayedToggle:
            processDelayedToggle(command.output, command.time1);
            break;

        case OpCode::delayedPulse:
            processDelayedPulse(command.output, command.time1, command.time2);
            break;

        case OpCode::repeatPulse:
            processRepeatPulse(command.output, command.time1, command.time2);
            break;

        case OpCode::tick:
            processTick(command.time1);
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
    output->_state = DigOutput::State::singlePulse;
    output->_timeCnt = pulseWidth;
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
    output->_timeCnt = delay;
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
    output->_timeCnt = delay;
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
    output->_timeCnt = delay;
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
    output->_timeCnt = delay;
    output->_time1 = pulseWidth;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'repeatPulse'.
/// \param    output: La sortida.
/// \param    pulseWidth: L'amplada del puls.
/// \param    spaceWidth: L'amplada del espai.
///
void DigOutputService::processRepeatPulse(
    DigOutput *output,
    unsigned pulseWidth,
    unsigned spaceWidth) {
    
    eosAssert(output != nullptr);

    if ((output->_state == DigOutput::State::idle) ||
        (output->_state == DigOutput::State::repeatInterval)) {
    	toggleOutput(output);
    }
    output->_state = DigOutput::State::repeatPulse;
    output->_timeCnt = pulseWidth;
    output->_time1 = pulseWidth;
    output->_time2 = spaceWidth;
}


/// ---------------------------------------------------------------------
/// \brief    Procesa la comanda 'tick'
/// \param    time: El interval de temps.
///
void DigOutputService::processTick(
    unsigned time) {

    for (auto output: _outputs) {

		switch (output->_state) {
			case DigOutput::State::singlePulse:
				if (output->_timeCnt <= time) {
					toggleOutput(output);
					output->_state = DigOutput::State::idle;
				}
				else
					output->_timeCnt -= time;
				break;

			case DigOutput::State::delayedSet:
			case DigOutput::State::delayedClear:
			case DigOutput::State::delayedToggle:
			case DigOutput::State::delayedPulse:
				if (output->_timeCnt <= time) {
					switch (output->_state) {
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
							output->_timeCnt = output->_time1;
							output->_state = DigOutput::State::singlePulse;
							break;

						default:
							break;
					}
				}
				else
					output->_timeCnt -= time;
				break;
                
            case DigOutput::State::repeatPulse:
            	if (output->_timeCnt <= time) {
            		toggleOutput(output);
            		output->_timeCnt = output->_time2;
            		output->_state = DigOutput::State::repeatInterval;
            	}
            	else
            		output->_timeCnt -= time;
                break;

            case DigOutput::State::repeatInterval:
            	if (output->_timeCnt <= time) {
            		toggleOutput(output);
            		output->_timeCnt = output->_time1;
            		output->_state = DigOutput::State::repeatPulse;
            	}
            	else
            		output->_timeCnt -= time;
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
        .opCode = OpCode::tick,
        .time1 = 1
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
    _state {State::idle},
	_timeCnt {0},
	_time1 {0},
	_time2 {0} {

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
