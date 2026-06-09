#include "eos.h"
#include "RTOS/rtosCriticalSection.h"
#include "RTOS/rtosKernel.h"
#include "Services/MsgBroker/eosMsgBrokerService.h"
#include "Services/MsgBroker/eosMsgPublisher.h"
#include "Services/MsgBroker/eosMsgSubscriber.h"


namespace eos {
	void __link(MsgBrokerService *service, MsgPublisher *publisher);
	void __link(MsgBrokerService *service, MsgSubscriber *subscriber);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    queueCapacity: Tamany de la cua interna.
///
eos::MsgBrokerService::MsgBrokerService():

	_actionQueue {_actionQueueSize} {
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un publicador. al servei.
/// \param    publisher: El publicador.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si tot es correcte.
///
bool eos::MsgBrokerService::addPublisher(
	MsgPublisher *publisher,
	uint32_t blockTime) {

	// Si el kernel esta en marxa, afegeix de forma asincrona
	//
	if ((rtos::Kernel::getState() == rtos::Kernel::State::running) &&
		getState() == eos::Service::State::run) {

		Action action = {
			.actionId = ActionID::addPublisher,
			.addPublisher {
				.publisher = publisher
			}
		};

		return _actionQueue.push(action, blockTime);
	}

	else {

		processAddPublisher(publisher);
		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un subscripto. al servei.
/// \param    subscriber: El subscriptor.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si tot es correcte.
///
bool eos::MsgBrokerService::addSubscriber(
	MsgSubscriber *subscriber,
	uint32_t blockTime) {

	// Si el kernel esta en marxa, afegeix de forma asincrona
	//
	if ((rtos::Kernel::getState() == rtos::Kernel::State::running) &&
		getState() == eos::Service::State::run) {

		Action action = {
			.actionId = ActionID::addSubscriber,
			.addSubscriber {
				.subscriber = subscriber
			}
		};

		return _actionQueue.push(action, blockTime);
	}

	else {

		processAddSubscriber(subscriber);
		return true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Envia una publicacio per la seva distribucio.
/// \param    publisher: El publicador.
/// \param    topic: El topic de la publicacio.
/// \param    payload: El contingut de la publicacio.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   True si tot es correcte.
///
bool eos::MsgBrokerService::publish(
	MsgPublisher *publisher,
	MsgTopic topic,
	MsgPayload payload,
	uint32_t blockTime) {

	Action action = {
		.actionId = ActionID::publish,
		.publish {
			.publisher = publisher,
			.topic = topic,
			.payload = payload
		}
	};
	return _actionQueue.push(action, blockTime);
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void eos::MsgBrokerService::onExecute() {

    while (!stopSignal()) {

    	Action action;
    	while (_actionQueue.pop(action, 1000)) {
    		switch (action.actionId) {
    			case ActionID::addPublisher:
    				processAddPublisher(action.addPublisher.publisher);
    				break;

    			case ActionID::addSubscriber:
    				processAddSubscriber(action.addSubscriber.subscriber);
    				break;

    			case ActionID::publish:
    				processPublish(
    					action.publish.publisher,
    					action.publish.topic,
						action.publish.payload);
    				break;
    		}
    	}
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un publicador al servei.
/// \param    publisher: El publicador.
///
void eos::MsgBrokerService::processAddPublisher(
	MsgPublisher *publisher) {

	rtos::CriticalSection::enter();

	if ((publisher != nullptr) &&
		(publisher->getService() == nullptr))
		__link(this, publisher);

	rtos::CriticalSection::exit();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un subscriptor al servei.
/// \param    subscriber: El subscriptor.
///
void eos::MsgBrokerService::processAddSubscriber(
	MsgSubscriber *subscriber) {

	rtos::CriticalSection::enter();

	if ((subscriber != nullptr) &&
		(subscriber->getService() == nullptr))
		__link(this, subscriber);

	rtos::CriticalSection::exit();
}


/// ----------------------------------------------------------------------
/// \brief    Envia una publicaciop als seus subscriptors.
/// \param    publisher: El publicador.
/// \param    topic: El topic de la publicacio.
/// \param    payload: El contingut de la publicacio.
///
void eos::MsgBrokerService::processPublish(
	MsgPublisher *publisher,
	MsgTopic topic,
	MsgPayload payload) {

	if ((publisher != nullptr) &&
		(publisher->getService() == this)) {

		for (auto subscriber: _subscriberList)
			if (subscriber->canAccept(topic))
				subscriber->dispatch(payload);

		publisher->done(payload);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Enllaça el publicador amb la llista de publicadors.
/// \param    service: El servei.
/// \param    publisher: El publicador.
///
void eos::__link(
	MsgBrokerService *service,
	MsgPublisher *publisher) {

	publisher->_service = service;
	service->_publisherList.pushFront(publisher);
}


/// ----------------------------------------------------------------------
/// \brief    Enllaça el subscriptor amb la llista de subscriptors.
/// \param    service: El servei.
/// \param    subscriber: El subscriptor.
///
void eos::__link(
	MsgBrokerService *service,
	MsgSubscriber *subscriber) {

	subscriber->_service = service;
	service->_subscriberList.pushFront(subscriber);
}
