#include "Services/eosAppLoop.h"


using namespace eos;


static AppLoopServiceConfiguration defaultConfiguration = {
	.serviceConfiguration = {
		.serviceName = "AppLoopService",
		.stackSize = 512,
		.priority = TaskPriority::normal
	}
};


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param pApplication: Aplicacio on afeigir el servei.
///
AppLoopService::AppLoopService(
	Application *pApplication):

	AppLoopService(pApplication, defaultConfiguration) {

}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param application: Aplicacio on afeigir el servei.
/// \param configuration: Parametres de configuracio.
///
AppLoopService::AppLoopService(
    Application *pApplication,
	const AppLoopServiceConfiguration &configuration):

    Service(pApplication, configuration.serviceConfiguration),
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
