#include "eos.h"
#include "Services/Messenger/eosMessengerService.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    application: L'aplicacio.
///
MessengerService::MessengerService():
	Service(),
	_messageQueue{10} {
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void MessengerService::onExecute() {

    while (!stopSignal()) {
    	Message message;
    	while (_messageQueue.pop(message, (unsigned) -1)) {
    	}
    }
}
