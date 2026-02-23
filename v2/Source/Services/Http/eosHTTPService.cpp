#include "eos.h"
#include "Services/eosHTTPService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor del objecte.
/// \param    application: L'aplicacio.
///
HTTPService::HTTPService():

    httpServer(eosHTTPService_Port) {

}



/// ----------------------------------------------------------------------
/// \brief    : Procesa la tasca del servei.
///
void HTTPService::onExecute() {

    httpServer.initialize();
    while (!stopSignal())
        httpServer.run();
}
