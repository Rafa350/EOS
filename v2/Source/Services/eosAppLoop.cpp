#include "Services/eosAppLoop.h"


using namespace eos;


static const char *serviceName = "AppLoopService";
static const unsigned stackSize = 512;
static const TaskPriority priority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param pApplication: Aplicacio a la que pertany el servei.
///
AppLoopService::AppLoopService(
    Application *pApplication):

    Service(pApplication, serviceName, stackSize, priority) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param pApplication: Aplicacio a la que pertany el servei.
/// \param stackSize: Tamany de la pila
/// \param priority: Prioritat
///
AppLoopService::AppLoopService(
    Application *pApplication,
    unsigned stackSize,
    TaskPriority priority):

    Service(pApplication, serviceName, stackSize, priority) {
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
