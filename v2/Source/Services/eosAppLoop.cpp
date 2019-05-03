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

    Service(pApplication, serviceName, stackSize, priority),
	initialized(false) {
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

    Service(pApplication, serviceName, stackSize, priority),
	initialized(false) {
}


/// ---------------------------------------------------------------------
/// \brief Inicialitzacio del servei abans del planificador.
///
void AppLoopService::onInitialize() {

}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio.
///
void AppLoopService::onTask() {

	if (!initialized) {
		onSetup();
		initialized = true;
	}
    onLoop();
}


/// ----------------------------------------------------------------------
/// \brief Executa les operacions inicials del servei. S'executa
///        nomes un cop.
///
void AppLoopService::onSetup() {

}


/// ----------------------------------------------------------------------
/// \brief Executa les operacions del servei. S'executa continuament.
///
void AppLoopService::onLoop() {

}
