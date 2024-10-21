#include "eos.h"
#include "Services/eosMessengerService.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    application: L'aplicacio.
///
MessengerService::MessengerService():
	Service() {
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un bus al servei.
/// \param    bus: El bus a afeigir.
///
void MessengerService::addPublisher(
    Publisher *publisher) {

    _publishers.pushFront(publisher);
}


void MessengerService::onExecute() {

    while (!stopSignal())
        Task::delay(1000);
}
