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
	Message *message) {

	MessageSubscriberEventArgs args = {
		.topicId = _topicId,
		.message = message
	};

	_event->execute(this, &args);
}
