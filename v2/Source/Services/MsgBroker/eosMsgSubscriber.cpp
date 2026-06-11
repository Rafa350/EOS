#include "eos.h"
#include "Services/MsgBroker/eosMsgSubscriber.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    topic: El topic de la publicacio que accepta
/// \param    event: Event
///
eos::MsgSubscriber::MsgSubscriber(
	MsgTopic topic,
	IMsgSubscriberEvent &event):

    _service {nullptr},
	_topic {topic},
	_event {&event} {

}


/// ----------------------------------------------------------------------
/// \brief    Genera un event
/// \param    payload: Contingut de la subscripcio.
///
void eos::MsgSubscriber::dispatch(
	MsgPayload *payload) {

	MsgSubscriberEventArgs args = {
		.topic = _topic,
		.payload = payload
	};

	_event->execute(this, &args);
}
