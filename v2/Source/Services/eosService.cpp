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
/// \brief    Inicia el servei.
///
void Service::start() {

	onStart();
}


/// ----------------------------------------------------------------------
/// \brief    Atura el servei.
///
void Service::stop() {

	onStop();
}


/// ----------------------------------------------------------------------
/// \brief    Executa les operacions del inici servei.
/// \return   True si es correcte i es pot continuar, false en cas d'error
///           i es vol finalitzar el proces.
///
bool Service::taskStart() {

    bool result = false;
    if (_state == State::initialized) {
        _state = State::running;
        result = onTaskStart();
        _state = State::started;
    }
    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Executa les operacions del servei.
///
bool Service::taskRun() {

    bool result = false;
    if (_state == State::started) {
        _state = State::running;
        result = onTask();
        _state = State::started;
    }
    return result;
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
/// \brief    Procesa l'inici del servei.
///
void Service::onStart() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa l'aturada del servei.
///
void Service::onStop() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa el inici de les operacions del servei.
///
bool Service::onTaskStart() {

    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les operacions del servei.
///
bool Service::onTask() {

    return true;
}
