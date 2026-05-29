#include "eos.h"
#include "Services/Messenger/eosMessageSubscriber.h"


eos::MessageSubscriber::MessageSubscriber(
	TopicID topicId,
	IMessageSubscriberEvent &event):

	_topicId {topicId},
	_event {&event} {

}
