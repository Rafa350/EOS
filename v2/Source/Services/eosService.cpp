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

	state(State::idle),
    application(nullptr),
	priority(Task::Priority::normal) {

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
/// \brief    Funcio d'execucio de la tasca.
/// \param    thread: La tasca.
///
void Service::run(
    Task *thread) {

    if (state == State::initialized) {
        state = State::running;
        while (state == State::running)
            task();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Configura el servei, abans de l'inici del planificador.
///
void Service::initialize() {

	if (state == State::idle) {
		onInitialize();
		state = State::initialized;
	}
}


/// ---------------------------------------------------------------------
/// \brief    Executa les operacions de la interrupcio tick.
///
void Service::tick() {

	if (state == State::running)
		onTick();
}


/// ----------------------------------------------------------------------
/// \brief    Executa les operacions del servei.
///
void Service::task() {

	if (state == State::running)
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
