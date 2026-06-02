#pragma once
#ifndef __eosMessagePublisher__
#define __eosMessagePublisher__


#include "eos.h"
#include "Services/Messenger/eosMessengerService.h"


namespace eos {

	class MessagePublisher: public MessagePublisherListNode {
		private:
			MessengerService * _service;
			TopicID const _topicId;

		public:
			MessagePublisher(TopicID topicId);

			void publish(Message *message, uint32_t blockTime);

			inline MessengerService *getService() const {
				return _service;
			}

			inline TopicID getTopicId() const {
				return _topicId;
			}

        friend void __link(MessengerService *service, MessagePublisher *publisher);
	};

}


#endif // __eosMessagePublisher__
