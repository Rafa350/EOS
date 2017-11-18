#include "Services/eosService.h"


using namespace eos;


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

    application(nullptr),
    name(name),
    task(stackSize, priority, name, this) {

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

	// Al drestruir-se, s'elimina ell mateix de la llista de serveis
	// de l'aplicacio.
	//
    if (application != nullptr)
        application->removeService(this);
}
