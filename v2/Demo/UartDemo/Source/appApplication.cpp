#include "eos.h"
#include "appApplication.h"
#include "appLoopService.h"
#include "Services/eosMessengerService.h"


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

	_loopService = new MyAppLoopService(this);
	_messengerService = new eos::MessengerService(this);

	eos::MessageBus<int> *msgBus1 = new eos::MessageBus<int>(10);
	_messengerService->addMessageBus(msgBus1);

	eos::MessageBus<bool> *msgBus2 = new eos::MessageBus<bool>(10);
	_messengerService->addMessageBus(msgBus2);
}
