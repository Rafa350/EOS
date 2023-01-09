#include "eos.h"
#include "Services/eosHTTPService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor del objecte.
/// \param    application: L'aplicacio.
///
HTTPService::HTTPService(
	Application *application):

	Service(application),
	httpServer(eosHTTPService_Port) {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void HTTPService::onInitialize() {

	setPriority(Task::Priority::high);

	httpServer.initialize();

}


/// ----------------------------------------------------------------------
/// \brief    : Procesa la tasca del servei.
///
void HTTPService::onTask(
	Task *task) {

    while (true) 
        httpServer.run();
}
