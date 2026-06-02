#include "eos.h"
#include "Services/Messenger/eosMessengerService.h"
#include "Services/Messenger/eosMessagePublisher.h"
#include "Services/Messenger/eosMessageSubscriber.h"


namespace eos {
	void __link(MessengerService *service, MessagePublisher *publisher);
	void __link(MessengerService *service, MessageSubscriber *subscriber);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    application: L'aplicacio.
///
eos::MessengerService::MessengerService(
	uint32_t queueCapacity):

	_actionQueue {queueCapacity} {
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un publicador. al servei.
/// \param    publisher: El publicador.
///
void eos::MessengerService::addPublisher(
	MessagePublisher *publisher,
	uint32_t blockTime) {

	Action action = {
		.actionId = ActionID::addPublisher,
		.addPublisher {
			.publisher = publisher
		}
	};
	_actionQueue.push(action, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un subscripto. al servei.
/// \param    subscriber: El subscriptor.
///
void eos::MessengerService::addSubscriber(
	MessageSubscriber *subscriber,
	uint32_t blockTime) {

	Action action = {
		.actionId = ActionID::addSubscriber,
		.addSubscriber {
			.subscriber = subscriber
		}
	};
	_actionQueue.push(action, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Envia una publicacio per la seva distribucio.
/// \param    publisher: El publicador.
/// \param    message: El missatge per publicar.
/// \param    blockTime: Temps maxim de bloqueig.
/// \notes    El publicador cal que estigui previament registrat en el servei.
///
bool eos::MessengerService::publish(
	MessagePublisher *publisher,
	Message *message,
	uint32_t blockTime) {

	Action action = {
		.actionId = ActionID::publish,
		.publish {
			.publisher = publisher,
			.message = message
		}
	};
	return _actionQueue.push(action, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void eos::MessengerService::onExecute() {

    while (!stopSignal()) {

    	Action action;
    	while (_actionQueue.pop(action, 0xFFFFFFFF)) {
    		switch (action.actionId) {
    			case ActionID::addPublisher:
    				processAddPublisher(action.addPublisher.publisher);
    				break;

    			case ActionID::addSubscriber:
    				processAddSubscriber(action.addSubscriber.subscriber);
    				break;

    			case ActionID::publish:
    				processPublish(action.publish.publisher, action.publish.message);
    				break;
    		}
    	}
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un publicador al servei.
/// \param    publisher: El publicador.
///
void eos::MessengerService::processAddPublisher(
	MessagePublisher *publisher) {

	rtos::Task::enterCriticalSection();

	if ((publisher != nullptr) &&
		(publisher->getService() == nullptr))
		__link(this, publisher);

	rtos::Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un subscriptor al servei.
/// \param    subscriber: El subscriptor.
///
void eos::MessengerService::processAddSubscriber(
	MessageSubscriber *subscriber) {

	rtos::Task::enterCriticalSection();

	if ((subscriber != nullptr) &&
		(subscriber->getService() == nullptr))
		__link(this, subscriber);

	rtos::Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Envia una publicaciop als seus subscriptors.
/// \param    publisher: El publicador.
/// \param    payload: La publicacio.
///
void eos::MessengerService::processPublish(
	MessagePublisher *publisher,
	Message *message) {

	if ((publisher != nullptr) &&
		(publisher->getService() == this)) {

		for (auto subscriber: _subscriberList) {
			if (publisher->getTopicId() == subscriber->getTopicId()) {
				subscriber->dispatch(message);
			}
		}
	}
}


void eos::__link(
	MessengerService *service,
	MessagePublisher *publisher) {

	publisher->_service = service;
	service->_publisherList.add(publisher);
}

void eos::__link(
	MessengerService *service,
	MessageSubscriber *subscriber) {

	subscriber->_service = service;
	service->_subscriberList.add(subscriber);
}
