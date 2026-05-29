#include "eos.h"
#include "Services/Messenger/eosMessageSubscriber.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    topicId: Identificador del topic
/// \param    event: Event
///
eos::MessageSubscriber::MessageSubscriber(
	TopicID topicId,
	IMessageSubscriberEvent &event):

	_topicId {topicId},
	_event {&event} {

}


void eos::MessageSubscriber::dispatch(
	void *payload) {

	MessageSubscriberEventArgs args = {
		.topicId = _topicId,
		.payload = &payload
	};

	_event->execute(this, &args);
}
