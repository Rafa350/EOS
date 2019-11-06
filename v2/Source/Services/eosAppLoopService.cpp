#include "eos.h"
#include "Services/eosAppLoopService.h"


using namespace eos;


static const ServiceConfiguration serviceConfiguration = {
	.serviceName = "AppLoopService",
	.stackSize = 512,
	.priority = TaskPriority::normal
};

static const AppLoopService::Configuration appLoopServiceConfiguration = {
	.serviceConfiguration = &serviceConfiguration
};


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    application: Aplicacio on afeigir el servei.
///
AppLoopService::AppLoopService(
	Application *application):

	AppLoopService(application, &appLoopServiceConfiguration) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: Aplicacio on afeigir el servei.
/// \param    configuration: Parametres de configuracio.
///
AppLoopService::AppLoopService(
    Application *application,
	const Configuration *configuration):

    Service(application, configuration->serviceConfiguration),
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
