#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"


using namespace eos;


int Service::idCount = 0;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param application: Aplicacio al que pertany.
/// \param name: Nom del servei.
///
Service::Service(
    Application *application,
    const char *name,
    unsigned stackSize,
    TaskPriority priority):

    id(idCount++),
    application(nullptr),
    name(name),
    thread(stackSize, priority, name, this) {

    // Si s'indica l'aplicacio, s'afegeix a la llista de
	// serveis d'aquesta.
	//
    if (application != nullptr)
        application->addService(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Service::~Service() {

	// Al destruir-se, s'elimina ell mateix de la llista de serveis
	// de l'aplicacio.
	//
    if (application != nullptr)
        application->removeService(this);
}


/// ----------------------------------------------------------------------
/// \brief Funcio d'execucio de la tasca.
/// \param pTask: La tasca.
///
void Service::run(
    Task *pThread) {

    while (true)
        task();
}


/// ----------------------------------------------------------------------
/// \brief Configura el servei, abans de l'inici del planificador.
///
void Service::initialize() {

	onInitialize();
}


/// ---------------------------------------------------------------------
/// \brief Executa les operacions de la interrupcio tick.
///
void Service::tick() {

	onTick();
}


/// ----------------------------------------------------------------------
/// \brief Executa les operacions del servei.
///
void Service::task() {

	onTask();
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio.
///
void Service::onInitialize() {

}


/// ----------------------------------------------------------------------
/// \brief Procesa les operacions de la interrupcio tick.
///
void Service::onTick() {

}


/// ----------------------------------------------------------------------
/// \brief Procesa les operacions del servei.
//
void Service::onTask() {

}
