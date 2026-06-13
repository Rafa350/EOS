#include "eos.h"
#include "RTOS/rtosCriticalSection.h"
#include "RTOS/rtosTask.h"
#include "Services/DigOutput/eosDigOutputService.h"
#include "System/eosMath.h"

#include "eos_digoutput_outputs.h"


// Parametres de la tasca del servei
//
constexpr const char *serviceName = "DigOutputs";
constexpr rtos::Task::Priority servicePriority = rtos::Task::Priority::normal;
constexpr uint32_t serviceStackDepth = 164;

// Parametres de configuracio del servei
//
constexpr uint32_t minPulseWidth = DigOutputService_MinPulseWidth;
constexpr uint32_t minDelay = DigOutputService_MinDelay;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::DigOutputService::DigOutputService():
	_outputChangedEvent {nullptr},
	_timeCounter {0},
	_actionQueue {_actionQueueSize} {

}


/// ----------------------------------------------------------------------
/// \brief    Crea i afegeix una sortida.
/// \param    pinDrv: El driver del pin
/// \param    tag: Etiqueta opcional
/// \return   La sortida.
///
eos::DigOutput* eos::DigOutputService::addOutput(
    eos::PinDriver *drv,
	uint32_t tag) {

    rtos::CriticalSection::enter();

    auto output = new Output(drv, tag);
	_outputs.pushFront(output);

    rtos::CriticalSection::exit();

    return output;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la sortida pertany al servei.
/// \param    output: La sortida.
/// \return   True si pertany, false en cas contrari.
///
bool eos::DigOutputService::containsOutput(
	eos::DigOutput *output) const {

	bool result = false;

	if (output != nullptr) {

		rtos::CriticalSection::enter();

		result = _outputs.contains(output);

		rtos::CriticalSection::exit();
	}

	return result;
}

/// ----------------------------------------------------------------------
/// \brief    Obte la sortida amb el tag especificat.
/// \param    tag: El tag de l'entrada a buscar.
/// \return   La sortida, o nullptr si no la troba.
///
eos::DigOutput *eos::DigOutputService::getOutput(
	uint32_t tag) const {

	DigOutput *result = nullptr;

	rtos::CriticalSection::enter();

	for (auto output: _outputs)
		if (output->getTag() == tag) {
			result = output;
			break;
		}

	rtos::CriticalSection::exit();

	return result;
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant la sortida especificada ha canviat el
///           seu valor. Genera un event 'OutputChanged'
/// \param    output: La sortida.
///
void eos::DigOutputService::onOutputChanged(
	eos::Output *output) {

	if (_outputChangedEvent != nullptr) {

    	OutputChangedEventArgs args = {
			.tag {output->getTag()},
			.value {output->getValue()}
		};

		_outputChangedEvent->execute(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat ACTIVE.
/// \param    output: La sortida.
///
void eos::DigOutputService::set(
    eos::DigOutput *output) {

#if DigOutputService_SafeMode == 1
	if (_outputs.contains(output)) {
#endif

		Action action = {
			.id {ActionID::set},
			.output {static_cast<Output*>(output)}
		};

		_actionQueue.push(action, unsigned(-1));

#if DigOutputService_SafeMode == 1
	}
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat IDLE.
/// \param    output: La sortida.
///
void eos::DigOutputService::clear(
    eos::DigOutput *output) {

#if DigOutputService_SafeMode == 1
	if (containsOutput(output)) {
#endif

		Action action = {
			.id {ActionID::clear},
			.output {static_cast<Output*>(output)}
		};

		_actionQueue.push(action, unsigned(-1));

#if DigOutputService_SafeMode == 1
	}
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat de la sortida.
/// \param    output: La sortida.
///
void eos::DigOutputService::toggle(
    eos::DigOutput *output) {

#if DigOutputService_SafeMode == 1
	if (containsOutput(output)) {
#endif

		Action action = {
			.id {ActionID::toggle},
			.output {static_cast<Output*>(output)}
		};

		_actionQueue.push(action, unsigned(-1));

#if DigOutputService_SafeMode == 1
	}
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'estat de la sortida.
/// \param    output: La sortida.
/// \param    state: L'estat a asignar.
///
void eos::DigOutputService::write(
    eos::DigOutput *output,
    bool state) {

#if DigOutputService_SafeMode == 1
	if (containsOutput(output)) {
#endif

		Action action = {
			.id {state ? ActionID::set : ActionID::clear},
			.output {static_cast<Output*>(output)}
		};

		_actionQueue.push(action, unsigned(-1));

#if DigOutputService_SafeMode == 1
	}
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio.
/// \param    output: La sortida.
/// \param    width: L'amplada del puls.
///
void eos::DigOutputService::pulse(
    eos::DigOutput *output,
    uint32_t width) {

#if DigOutputService_SafeMode == 1
	if (containsOutput(output)) {
#endif

		Action action = {
			.id {ActionID::pulse},
			.output {static_cast<Output*>(output)},
			.time1 {eos::Math::max(width, minPulseWidth)}
		};

		_actionQueue.push(action, unsigned(-1));

#if DigOutputService_SafeMode == 1
	}
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio retardat.
/// \param    output: La sortida.
/// \param    delay: El retard del puls.
/// \param    width: L'amplada del puls.
///
void eos::DigOutputService::delayedPulse(
    eos::DigOutput *output,
    uint32_t delay,
    uint32_t width) {

#if DigOutputService_SafeMode == 1
	if (containsOutput(output)) {
#endif

		Action action = {
			.id {ActionID::delayedPulse},
			.output {static_cast<Output*>(output)},
			.time1 {eos::Math::max(delay, minDelay)},
			.time2 {eos::Math::max(width, minPulseWidth)}
		};

		_actionQueue.push(action, unsigned(-1));

#if DigOutputService_SafeMode == 1
	}
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el valor d'una sortida.
/// \param    output: La sortida.
/// \return   L'estat de la sortida.
///
bool eos::DigOutputService::read(
	eos::DigOutput *output) {

#if DigOutputService_SafeMode == 1
	if (containsOutput(output)) {
#endif

		rtos::CriticalSection::enter();

		auto out = static_cast<Output*>(output);
		bool value = out->getValue();

		rtos::CriticalSection::exit();

		return value;

#if DigOutputService_SafeMode == 1
	}
	else
		return false;
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
/// \param    params: Els parametres.
///
void eos::DigOutputService::onInitialize(
	eos::Service::ServiceParams &params) {

	params.name = serviceName;
	params.stackDepth = serviceStackDepth;
	params.priority = servicePriority;
}


/// ----------------------------------------------------------------------
/// \brief    Tasca del servei.
///
void eos::DigOutputService::onExecute() {

	while (!stopSignal()) {
		Action action;
		while (_actionQueue.pop(action, (unsigned) -1))
			processAction(action);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les accions.
/// \param    action: L'accio.
///
void eos::DigOutputService::processAction(
	const Action &action) {

    switch (action.id) {
        case ActionID::set:
            processSet(action.output);
            break;

        case ActionID::clear:
            processClear(action.output);
            break;

        case ActionID::toggle:
            processToggle(action.output);
            break;

        case ActionID::pulse:
            processPulse(action.output, action.time1);
            break;

        case ActionID::delayedSet:
            processDelayedSet(action.output, action.time1);
            break;

        case ActionID::delayedClear:
            processDelayedClear(action.output, action.time1);
            break;

        case ActionID::delayedToggle:
            processDelayedToggle(action.output, action.time1);
            break;

        case ActionID::delayedPulse:
            processDelayedPulse(action.output, action.time1, action.time2);
            break;

        case ActionID::tick:
            processTick();
            break;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'clear'
/// \param    output: La sortida.
///
void eos::DigOutputService::processClear(
    eos::Output *output) {

	if (output->getValue()) {
		output->clear();
		onOutputChanged(output);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'set'
/// \param    output: La sortida.
///
void eos::DigOutputService::processSet(
    eos::Output *output) {

	if (!output->getValue()) {
		output->set();
		onOutputChanged(output);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    output: La sortida.
///
void eos::DigOutputService::processToggle(
    eos::Output *output) {

	output->toggle();
	onOutputChanged(output);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'pulse'.
/// \param    output: La sortida.
/// \param    pulseWidth: L'amplada del puls.
///
void eos::DigOutputService::processPulse(
    eos::Output *output,
    uint32_t pulseWidth) {

	bool oldValue = output->getValue();
	output->pulse(_timeCounter, pulseWidth);
	if (oldValue != output->getValue())
		onOutputChanged(output);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedSet'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void eos::DigOutputService::processDelayedSet(
    eos::Output *output,
    uint32_t delay) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedClear'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void eos::DigOutputService::processDelayedClear(
    eos::Output *output,
    uint32_t delay) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedToggle'.
/// \param    output: La sortida.
/// \param    delay: El retard.
///
void eos::DigOutputService::processDelayedToggle(
    eos::Output *output,
    uint32_t delay) {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'delayedPulse'.
/// \param    output: La sortida.
/// \param    delay: El retard del puls.
/// \param    pulseWidth: L'amplada del puls.
///
void eos::DigOutputService::processDelayedPulse(
    eos::Output *output,
    uint32_t delay,
    uint32_t pulseWidth) {

	output->delayedPulse(_timeCounter, delay, pulseWidth);
}


/// ---------------------------------------------------------------------
/// \brief    Procesa la comanda 'tick'
///
void eos::DigOutputService::processTick() {

	for (auto o: _outputs) {
    	auto output = static_cast<Output*>(o);

    	bool oldValue = output->getValue();
		output->tick(_timeCounter);
		if (oldValue != output->getValue())
			onOutputChanged(output);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio del temportitzador
/// \remarks  ATENCIO: Es procesa dins d'una interrupcio.
///
void eos::DigOutputService::tickISR() {

	// Incrementa el contador de temps
	//
	_timeCounter += 1;

    Action action = {
        .id {ActionID::tick}
    };

    // Es porta el missatge en la cua, per procesar-l'ho en la tasca,
    // fora de la interrupcio.
    //
    _actionQueue.pushISR(action);
}
