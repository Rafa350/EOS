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
	Application* application) :

    application(nullptr),
	stackSize(512),
	priority(Task::Priority::normal),
    initialized(false),
	name("SERVICE") {

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
    if (application != nullptr)
        application->removeService(this);
}


/// ----------------------------------------------------------------------
/// \brief    Configura el servei, abans de l'inici del planificador.
///
void Service::initialize() {

	if (!initialized) {
		onInitialize();
        initialized = true;
	}
}


/// ---------------------------------------------------------------------
/// \brief    Executa les operacions de la interrupcio tick.
///
void Service::tick() {

	if (initialized)
		onTick();
}


/// ----------------------------------------------------------------------
/// \brief    Executa les operacions del servei.
///
void Service::task() {

    if (initialized)
        onTask();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la inicialitzacio.
///
void Service::onInitialize() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les operacions de la interrupcio tick.
///
void Service::onTick() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les operacions del servei.
//
void Service::onTask() {

}
