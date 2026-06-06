#include "eos.h"
#include "Services/eosService.h"
#include "System/eosRTOSApplication.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Service::Service():
	_taskEvent {*this, &Service::taskEventHandler},
	_task {nullptr},
	_state {State::stop},
	_stopSignal {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
Service::~Service() {

	if (_task != nullptr)
		delete _task;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia l'execucio del servei.
///
void Service::start() {

	if (_state == State::stop) {

		ServiceParams params = {
			.name = _defaultName,
			.priority = _defaultPriority,
			.stackDepth = _defaultStackDepth
		};

		onInitialize(params);

		onStart();
		_task = new rtos::Task(
			params.stackDepth,
			params.priority,
			params.name,
			_taskEvent);
		_state = State::run; //******** Aqui?
	}
}


/// ----------------------------------------------------------------------
/// \brief    Atura l'execucio del servei.
///
void Service::stop() {

	if (_state == State::run) {
		onStop();
		_stopSignal = true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si cal aturar el servei.
/// \return   True en cas afirmatiu.
///
bool Service::stopSignal() const {

	return _stopSignal;
}


/// ----------------------------------------------------------------------
/// \brief    Handler de la tasca.
/// \params   args: Parametres.
///
void Service::taskEventHandler(
	rtos::Task *task,
	rtos::Task::EventArgs *args) {

	_state = State::run; //********* O aqui?
	onStarted();
	onExecute();
	_state = State::stop;
	onStopped();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
/// \param    params: Els parametres del servei.
///
void Service::onInitialize(
	ServiceParams &paramms) {

}


/// ----------------------------------------------------------------------
/// \brief    Proces al inici del servei.
///
void Service::onStart() {

}


/// ----------------------------------------------------------------------
/// \brief    Proces un cop iniciat el servei.
///
void Service::onStarted() {

}


/// ----------------------------------------------------------------------
/// \brief    Proces al aturar el servei.
///
void Service::onStop() {

}


/// ----------------------------------------------------------------------
/// \brief    Proces un cop aturar el servei.
///
void Service::onStopped() {

}
