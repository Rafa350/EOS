#include "eos.h"
#include "Services/MsgBroker/eosMsgSubscriber.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    topic: El topic de la publicacio que accepta
/// \param    event: Event
///
eos::MsgSubscriber::MsgSubscriber(
	MsgTopic topic,
	ISubscriptionEvent &subscriptionEvent):

    _service {nullptr},
	_topic {topic},
	_subscriptionEvent {&subscriptionEvent} {

}


/// ----------------------------------------------------------------------
/// \brief    Genera el event 'Subscription'
/// \param    payload: El payload.
///
void eos::MsgSubscriber::onSubscription(
	MsgPayload *payload) {

	if (_subscriptionEvent != nullptr) {

		SubscriptionEventArgs args = {
			.topic = _topic,
			.payload = payload
		};

		_subscriptionEvent->execute(this, &args);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Despacha el payload.
/// \param    payload: Contingut de la subscripcio.
///
void eos::MsgSubscriber::dispatch(
	MsgPayload *payload) {

	onSubscription(payload);
}
