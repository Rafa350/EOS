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

    _publishers.push_front(publisher);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void MessengerService::onInitialize() {

    // Crea una tasca per cada publicador
    //
    for (auto publisher: _publishers) {

/*        Task *task = new Task(
            getStackSize(),
            getPriority(),
            getName(),
            &_busTaskEventCallback,
            static_cast<void*>(bus));*/
    }
}


void MessengerService::onTask() {

    while (true)
        Task::delay(1000);
}
