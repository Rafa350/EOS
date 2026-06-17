#include "eos.h"
#include "Services/MsgDispatcher/eosMsgDispatcherService.h"
#include "System/eosTime.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
eos::MsgDispatcherService::MsgDispatcherService():
	_actionQueue {10},
	_dispatchFinishedEvent {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un listener de forma asincrona
/// \param    typeId: El tipus de missatge que accepta.
/// \param    listener: El listener.
///
void eos::MsgDispatcherService::addListenerImpl(
	MsgListener *listener,
	Time blockTime) {

	Action action = {
		.id {ActionID::addListener},
		.addListener {
			.listener {listener}
		}
	};

	_actionQueue.push(action, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Envia un missatge de forma asincrona
/// \param    typeId: El identificasdor del tipus de missatge
/// \param    message: El missatge.
/// \param    blockTime: Temps maxim de bloqueig.
///
void eos::MsgDispatcherService::postImpl(
	uint32_t typeId,
	Message *message,
	Time blockTime) {

	Action action = {
		.id {ActionID::postMessage},
		.postMessage {
			.typeId {typeId},
			.message {message}
		}
	};

	_actionQueue.push(action, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Es crida quant ha acabat de despatxar el missatge a tots
///           els listeners
/// \param    message: El missatge.
///
void eos::MsgDispatcherService::onDispatchFinished(
	Message *message) {

	if (_dispatchFinishedEvent != nullptr) {

		DispatchFinishedEventArgs args = {
			.message {message}
		};
		_dispatchFinishedEvent->execute(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Executa la tasca del servei.
///
void eos::MsgDispatcherService::onExecute() {

	while (!stopSignal()) {

		Action action;
		while (_actionQueue.pop(action, Time::fromMiliseconds(1000))) {

			switch (action.id) {
				case ActionID::postMessage: {

					auto typeId = action.postMessage.typeId;
					auto message = action.postMessage.message;

					for (auto listener: _listenerList)
						if (listener->getTypeId() == typeId) {
							listener->dispatch(message);
						}

					onDispatchFinished(message);
				}
				break;

				case ActionID::addListener: {
					auto listener = action.addListener.listener;
					_listenerList.pushFront(listener);
				}
				break;
			}
		}
	}
}
