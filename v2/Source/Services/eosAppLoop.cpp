#include "Services/eosAppLoop.h"


using namespace eos;


static const char *serviceName = "AppLoopService";
static const unsigned stackSize = 512;
static const TaskPriority priority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param application: Aplicacio a la que pertany el servei.
///
AppLoopService::AppLoopService(
    Application *application):

    Service(application, serviceName, stackSize, priority),
	initialized(false) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param application: Aplicacio a la que pertany el servei.
/// \param stackSize: Tamany de la pila
/// \param priority: Prioritat
///
AppLoopService::AppLoopService(
    Application *application, 
    unsigned stackSize, 
    TaskPriority priority):

    Service(application, serviceName, stackSize, priority),
	initialized(false) {
}


/// ---------------------------------------------------------------------
/// \brief Inicialitzacio.
///
void AppLoopService::onSetup() {
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio.
///
void AppLoopService::onLoop() {
}
