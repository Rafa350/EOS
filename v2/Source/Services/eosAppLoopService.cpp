#include "eos.h"
#include "Services/eosAppLoopService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    application: Aplicacio on afeigir el servei.
///
AppLoopService::AppLoopService():
	Service() {
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

	onSetup();
	while (!onLoop())
		continue;
}


/// ----------------------------------------------------------------------
/// \brief Executa les operacions inicials del servei. S'executa
///        nomes un cop.
///
void AppLoopService::onSetup() {

}


/// ----------------------------------------------------------------------
/// \brief    Executa les operacions del servei.
/// \return   True si cal finalitzar el proces.
///
bool AppLoopService::onLoop() {

	return true;
}
