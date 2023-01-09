#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"
#include "System/eosApplication.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: Aplicacio al que pertany.
///
Service::Service(
	Application *application) :

    _application(nullptr),
	_stackSize(512),
	_priority(Task::Priority::normal),
    _initialized(false),
	_name("SERVICE") {

    // Si s'indica l'aplicacio, aleshores s'afegeix a la llista de
	// serveis d'aquesta.
	//
    if (application != nullptr)
        application->addService(this);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
Service::~Service() {

	// Al destruir-se, s'elimina ell mateix de la llista de serveis
	// de l'aplicacio.
	//
    if (_application != nullptr)
        _application->removeService(this);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void Service::initialize() {

	if (!_initialized) {
		onInitialize();
        _initialized = true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el servei.
///
void Service::terminate() {

    if (_initialized) {
        onTerminate();
        _initialized = false;
    }
}


/// ---------------------------------------------------------------------
/// \brief    Executa les operacions de la interrupcio tick.
///
#if Eos_ApplicationTickEnabled
void Service::tick() {

	if (_initialized)
		onTick();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Executa les operacions del servei.
///
void Service::task() {

    if (_initialized)
        onTask();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio.
///
void Service::onInitialize() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa la finalitzacio.
///
void Service::onTerminate() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les operacions de la interrupcio tick.
///
#if Eos_ApplicationTickEnabled
void Service::onTick() {

}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa les operacions del servei.
///
void Service::onTask() {

}
