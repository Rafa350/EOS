module Eos.Services.MsgDispatcher;


import Eos.System.Core.Queue;
import Eos.System.Core.Ticks;
import Eos.Types;


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor
///
MsgDispatcherService::MsgDispatcherService():
	_commandQueue {_commandQueueSize},
	_dispatchFinishedEvent {nullptr} {

}


/// ----------------------------------------------------------------------
/// @brief    Afegeix un listener de forma asincrona
/// @param    typeId: El tipus de missatge que accepta.
/// @param    listener: El listener.
///
void MsgDispatcherService::addListenerImpl(
	MsgListener *listener,
	Ticks blockTime) {

	Command command = {
		.id {CommandID::addListener},
		.addListener {
			.listener {listener}
		}
	};

	_commandQueue.push(command, blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Envia un missatge de forma asincrona
/// @param    typeId: El identificasdor del tipus de missatge
/// @param    message: El missatge.
/// @param    blockTime: Temps maxim de bloqueig.
///
void MsgDispatcherService::postImpl(
	UInt32 typeId,
	Message *message,
	Ticks blockTime) {

	Command command = {
		.id {CommandID::postMessage},
		.postMessage {
			.typeId {typeId},
			.message {message}
		}
	};

	_commandQueue.push(command, blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Es crida quant ha acabat de despatxar el missatge a tots
///           els listeners
/// @param    message: El missatge.
///
void MsgDispatcherService::onDispatchFinished(
	Message *message) {

	if (_dispatchFinishedEvent != nullptr) {

		DispatchFinishedEventArgs args = {
			.message {message}
		};
		_dispatchFinishedEvent->execute(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// @brief    Executa la tasca del servei.
///
void MsgDispatcherService::onExecute() {

	while (!stopSignal()) {

		Command command;
		while (_commandQueue.pop(command, Ticks::fromMiliseconds(1000))) {

			switch (command.id) {
				case CommandID::postMessage: {

					auto typeId = command.postMessage.typeId;
					auto message = command.postMessage.message;

					for (auto listener: _listenerList)
						if (listener->getTypeId() == typeId) {
							listener->dispatch(message);
						}

					onDispatchFinished(message);
				}
				break;

				case CommandID::addListener: {
					auto listener = command.addListener.listener;
					_listenerList.pushFront(listener);
				}
				break;
			}
		}
	}
}
