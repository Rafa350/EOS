#include "eos.h"
#include "Services/DigOutput/eosDigOutputService.h"
#include "System/Core/eosTask.h"

#include "eos_digoutput_outputs.h"

#include <cmath>
#include <limits>

#include "HTL/htlINT.h"


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
	_actionQueue {_actionQueueSize} {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
DigOutputService::~DigOutputService() {

	removeOutputs();
}


/// ----------------------------------------------------------------------
/// \brief    Crea i afegeix una sortida.
/// \param    pinDrv: El driver del pin
/// \param    tag: Etiqueta opcional
/// \return   La sortida.
///
DigOutput* DigOutputService::addOutput(
    PinDriver *drv,
	unsigned tag) {

    Task::enterCriticalSection();

    auto output = new Output(drv, tag);
	_outputs.pushFront(output);

    Task::exitCriticalSection();

    return output;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una sortida del servei.
/// \param    output: La sortida a eliminar.
/// \remarks  Nomes es poden eliminar sortides, quan el servei no
///           esta inicialitzat.
///
void DigOutputService::removeOutput(
    DigOutput *output) {

    Task::enterCriticalSection();

    if (_outputs.contains(output))
        _outputs.remove(output);

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina totes les sortides del servei.
/// \remarks  Nomes es poden eliminar sortides, quan el servei
///           no esta inicialitzat.
///
void DigOutputService::removeOutputs() {

    Task::enterCriticalSection();

   	_outputs.clear();

    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Notifica un canvi en l'estat d'una sortida.
/// \param    output: La sortida.
///
void DigOutputService::raiseChangedNotificationEvent(
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

    Action action = {
        .id {ActionID::set},
        .output {static_cast<Output*>(output)}
    };

    _actionQueue.push(action, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Posa la sortida en estat IDLE.
/// \param    output: La sortida.
///
void DigOutputService::clear(
    DigOutput *output) {

    Action action = {
        .id {ActionID::clear},
        .output {static_cast<Output*>(output)}
    };

    _actionQueue.push(action, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat de la sortida.
/// \param    output: La sortida.
///
void DigOutputService::toggle(
    DigOutput *output) {

    Action action = {
        .id {ActionID::toggle},
        .output {static_cast<Output*>(output)}
    };

    _actionQueue.push(action, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Asigna l'estat de la sortida.
/// \param    output: La sortida.
/// \param    state: L'estat a asignar.
///
void DigOutputService::write(
    DigOutput *output,
    bool state) {

    Action action = {
        .id {state ? ActionID::set : ActionID::clear},
        .output {static_cast<Output*>(output)}
    };

    _actionQueue.push(action, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Genera un puls de conmutacio.
/// \param    output: La sortida.
/// \param    width: L'amplada del puls.
///
void DigOutputService::pulse(
    DigOutput *output,
    unsigned width) {

    Action action = {
        .id {ActionID::pulse},
        .output {static_cast<Output*>(output)},
        .time1 {std::max(width, minPulseWidth)}
    };

    _actionQueue.push(action, unsigned(-1));
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

    Action action = {
        .id {ActionID::delayedPulse},
        .output {static_cast<Output*>(output)},
        .time1 {std::max(delay, minDelay)},
        .time2 {std::max(width, minPulseWidth)}
    };

    _actionQueue.push(action, unsigned(-1));
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el valor d'una sortida.
/// \param    output: La sortida.
/// \return   L'estat de la sortida.
///
bool DigOutputService::read(
	DigOutput *output) {

    Task::enterCriticalSection();

    auto out = static_cast<Output*>(output);
    bool value = out->getValue();

    Task::exitCriticalSection();

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
		Action action;
		while (_actionQueue.pop(action, (unsigned) -1))
			actionDispatcher(action);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les accions.
/// \param    action: L'accio.
///
void DigOutputService::actionDispatcher(
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
void DigOutputService::processClear(
    Output *output) {

	if (output->getValue()) {
		output->clear();
		raiseChangedNotificationEvent(output);
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
		raiseChangedNotificationEvent(output);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la comanda 'toggle'
/// \param    output: La sortida.
///
void DigOutputService::processToggle(
    Output *output) {

	output->toggle();
	raiseChangedNotificationEvent(output);
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
		raiseChangedNotificationEvent(output);
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
			raiseChangedNotificationEvent(output);
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

    Action action = {
        .id {ActionID::tick}
    };

    // Es porta el missatge en la cua, per procesar-l'ho en la tasca,
    // fora de la interrupcio.
    //
    _actionQueue.pushISR(action);
}
