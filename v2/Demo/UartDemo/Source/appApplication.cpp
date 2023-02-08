#include "eos.h"
#include "appApplication.h"
#include "appLoopService.h"
#include "Services/eosMessengerService.h"
#include "System/Core/eosTask.h"


using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication() {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

	_loopService = new MyAppLoopService();
	addService(_loopService, eos::Task::Priority::normal, 512, "LOOP");

	_messengerService = new eos::MessengerService();
	addService(_messengerService, eos::Task::Priority::normal, 512, "MESSENGER");

	eos::MessageBus<int> *msgBus1 = new eos::MessageBus<int>(10);
	_messengerService->addMessageBus(msgBus1);

	eos::MessageBus<bool> *msgBus2 = new eos::MessageBus<bool>(10);
	_messengerService->addMessageBus(msgBus2);
}
