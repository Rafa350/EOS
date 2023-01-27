#include "eos.h"
#include "Services/eosMessengerService.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    application: L'aplicacio.
///
MessengerService::MessengerService():
	Service(),
    _busTaskEventCallback(*this, &MessengerService::busTaskEventHandler) {

}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un bus al servei.
/// \param    bus: El bus a afeigir.
///
void MessengerService::addMessageBus(
	IMessageBus *bus) {

	_busses.pushBack(bus);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void MessengerService::onInitialize() {

    // Crea una tasca per cada bus
    //
    for (auto bus: _busses) {

/*        Task *task = new Task(
            getStackSize(),
            getPriority(),
            getName(),
            &_busTaskEventCallback,
            static_cast<void*>(bus));*/
    }
}


/// ----------------------------------------------------------------------
/// \brief    Handler del event de la tasca
/// \param    args: Parametres.
///
void MessengerService::busTaskEventHandler(
    const Task::EventArgs &args) {

    IMessageBus *bus = static_cast<IMessageBus*>(args.params);
    bus->processLoop();
}