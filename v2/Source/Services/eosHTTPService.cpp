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
/// \brief    Inicialitza el servei.
///
void HTTPService::onInitialize() {

}


/// ----------------------------------------------------------------------
/// \brief    : Procesa la tasca del servei.
///
void HTTPService::onTask() {

    httpServer.initialize();
    while (true) 
        httpServer.run();
}
