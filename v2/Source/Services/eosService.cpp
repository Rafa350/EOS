#include "Services/eosService.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param application: Aplicacio al que pertany.
/// \param name: Nom del servei.
///
Service::Service(
    Application *_application,
    const char *_name,
    unsigned stackSize,
    TaskPriority priority):
    
    application(nullptr),
    name(_name),
    task(stackSize, priority, _name, this) {

    if (_application != nullptr)
        _application->addService(this);
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Service::~Service() {
     
    if (application != nullptr)
        application->removeService(this);
 }