#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"
#include "System/eosRTOSApplication.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Service::Service():
	_state(State::created) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void Service::initialize() {

	if (_state == State::created) {
		onInitialize();
        _state = State::initialized;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el servei.
///
void Service::terminate() {

    if ((_state == State::stopped) || (_state == State::started)) {
        onTerminate();
        _state = State::terminated;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Executa les operacions del servei.
///
void Service::taskStart() {

    if (_state == State::initialized) {
        _state = State::running;
        onTaskStart();
        _state = State::started;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Executa les operacions del servei.
///
void Service::taskRun() {

    if (_state == State::started) {
        _state = State::running;
        onTask();
        _state = State::started;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio del servei
///
void Service::onInitialize() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa la finalitzacio del servei
///
void Service::onTerminate() {

}



/// ----------------------------------------------------------------------
/// \brief    Procesa el inici de les operacions del servei.
///
void Service::onTaskStart() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les operacions del servei.
///
void Service::onTask() {

}
