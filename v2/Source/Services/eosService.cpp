#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param application: Aplicacio al que pertany.
/// \param name: Nom del servei.
///
Service::Service(
    Application *pApplication,
    const char *name,
    unsigned stackSize,
    TaskPriority priority):

    pApplication(nullptr),
    name(name),
    task(stackSize, priority, name, this) {

    // Si s'indica l'aplicacio, s'afegeix a la llista de
	// serveis d'aquesta.
	//
    if (pApplication != nullptr)
        pApplication->addService(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Service::~Service() {

	// Al drestruir-se, s'elimina ell mateix de la llista de serveis
	// de l'aplicacio.
	//
    if (pApplication != nullptr)
        pApplication->removeService(this);
}


/// ----------------------------------------------------------------------
/// \brief Funcio d'execucio de la tasca.
/// \param pTask: La tasca.
///
void Service::run(
    Task *pTask) {

    // Crida continuament a onTask
    //
    while (true)
        onTask();
}


/// ----------------------------------------------------------------------
/// \brief Procesa la inicialitzacio del servei.
///
void Service::onInitialize() {

}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei.
//
void Service::onTask() {

}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio tick.
///
void Service::onTick() {

}
