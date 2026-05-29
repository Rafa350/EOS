#include "eos.h"
#include "Services/Messenger/eosMessengerService.h"
#include "Services/Messenger/eosMessagePublisher.h"
#include "Services/Messenger/eosMessageSubscriber.h"


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

	rtos::Task::enterCriticalSection();

	if (publisher->getService() == nullptr) {

		Action action = {
			.actionId = ActionID::addPublisher,
			.addPublisher {
				.publisher = publisher
			}
		};

		_actionQueue.push(action, blockTime);
	}

	rtos::Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un subscripto. al servei.
/// \param    subscriber: El subscriptor.
///
void eos::MessengerService::addSubscriber(
	MessageSubscriber *subscriber,
	uint32_t blockTime) {

	rtos::Task::enterCriticalSection();

	if (subscriber->getService() == nullptr) {

		Action action = {
			.actionId = ActionID::addSubscriber,
			.addSubscriber {
				.subscriber = subscriber
			}
		};

		_actionQueue.push(action, blockTime);
	}

	rtos::Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief    Envia una publicacio per la seva distribucio.
/// \param    publisher: El publicador.
/// \param    payload: El contingut de la publicacio.
/// \param    blockTime: Temps maxim de bloqueig.
/// \notes    El publicador cal que estigui previament registrat en el servei.
///
bool eos::MessengerService::publish(
	MessagePublisher *publisher,
	void *payload,
	uint32_t blockTime) {

	bool result = false;

	rtos::Task::enterCriticalSection();

	if (publisher->getService() == this) {

		Action action = {
			.actionId = ActionID::publish,
			.publish {
				.publisher = publisher,
				.payload = &payload
			}
		};

		result = _actionQueue.push(action, blockTime);
	}

    rtos::Task::exitCriticalSection();

	return result;
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
    				processPublish(action.publish.publisher, action.publish.payload);
    				break;
    		}
    	}
    }
}


void eos::MessengerService::processAddPublisher(
	MessagePublisher *publisher) {

	rtos::Task::enterCriticalSection();

	_publisherList.add(publisher);
	publisher->_service = this;

	rtos::Task::exitCriticalSection();
}


void eos::MessengerService::processAddSubscriber(
	MessageSubscriber *subscriber) {

	rtos::Task::enterCriticalSection();

	_subscriberList.add(subscriber);
	subscriber->_service = this;

	rtos::Task::exitCriticalSection();
}


void eos::MessengerService::processPublish(
	MessagePublisher *publisher,
	void *payload) {

	for (auto subscriber: _subscriberList) {
		if (publisher->getTopicId() == subscriber->getTopicId()) {
    		subscriber->dispatch(payload);
		}
	}
}
