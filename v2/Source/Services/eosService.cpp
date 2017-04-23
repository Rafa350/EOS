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

    if (application != nullptr)
        application->addService(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Service::~Service() {

    if (application != nullptr)
        application->removeService(this);
 }
