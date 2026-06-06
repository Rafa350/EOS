#include "eos.h"
#include "Services/MsgBroker/eosMsgSubscriber.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    publicationId: Identificador de la publicacio.
/// \param    event: Event
///
eos::MsgSubscriber::MsgSubscriber(
	MsgTopic topic,
	IMsgSubscriberEvent &event):

	_topic {topic},
	_event {&event} {

}


void eos::MsgSubscriber::dispatch(
	MsgPayload payload) {

	MsgSubscriberEventArgs args = {
		.topic = _topic,
		.payload = payload
	};

	_event->execute(this, &args);
}
