#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"
#include "System/eosRTOSApplication.h"
#include "System/Core/eosTask.h"


using namespace eos;


constexpr const char *serviceName = "Service";
constexpr unsigned serviceStackSize = 256;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Service::Service():
	_state {State::stop},
	_task {nullptr},
	_taskCallback {*this, &Service::taskCallbackHandler},
	_stopSignal {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicia l'execucio del servei.
///
void Service::start() {

	if (_state == State::stop) {

		ServiceParams params = {
			.name = serviceName,
			.priority = Task::Priority::normal,
			.stackSize = serviceStackSize
		};

		onInitialize(params);

		onStart();
		_task = new Task(
				params.stackSize,
				params.priority,
				params.name,
				&_taskCallback,
				nullptr);
		_state = State::run;
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
void Service::taskCallbackHandler(
	const TaskCallbackArgs &args) {

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
