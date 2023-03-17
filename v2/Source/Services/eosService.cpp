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
        _state = State::ready;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el servei.
///
void Service::terminate() {

    if (_state == State::ready) {
        onTerminate();
        _state = State::finished;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Executa les operacions del servei.
///
void Service::task() {

    if (_state == State::ready) {
    	_state = State::running;
        onTask();
        _state = State::ready;
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
/// \brief    Procesa les operacions del servei.
///
void Service::onTask() {

}
