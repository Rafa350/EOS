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

	_queue {queueCapacity} {
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un publicador. al servei.
/// \param    publisher: El publicador.
///
void eos::MessengerService::addPublisher(
	MessagePublisher *publisher) {

	if (publisher->_service == nullptr) {
		_publisherList.add(publisher);
		publisher->_service = this;
	}
}

void eos::MessengerService::removePublisher(
	MessagePublisher *publisher) {

	if (publisher->_service == this) {
		publisher->_service = nullptr;
		_publisherList.remove(publisher);
	}
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
	const MessagePayload &payload,
	uint32_t blockTime) {

	if (_publisherList.contains(publisher)) {

		QueueItem item = {
			.publisher = publisher,
			.payload = &payload
		};

		return _queue.push(item, blockTime);
	}

	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void eos::MessengerService::onExecute() {

    while (!stopSignal()) {

    	// Espera que hagin publicadors en la cua
    	//
    	QueueItem queueItem;
    	while (_queue.pop(queueItem, 0xFFFFFFFF)) {
    		auto publisher = queueItem.publisher;
    		for (auto subscriber: _subscriberList) {
    			if (publisher->getTopicId() == subscriber->getTopicId()) {
    	    		auto payload = queueItem.payload;
    	    		subscriber->dispatch(*payload);
    			}
    		}
    	}
    }
}
