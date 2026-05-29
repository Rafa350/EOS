#pragma once


#include "eos.h"
#include "Services/Messenger/eosMessengerService.h"
#include "System/Core/eosQueue.h"


namespace eos {

	class MessagePublisher: public MessagePublisherListNode {

		private:
			MessengerService * _service;
			TopicID const _topicId;

		public:
			MessagePublisher(TopicID topicId);

			void publish(const MessagePayload &payload, uint32_t blockTime);

			TopicID getTopicId() const {
				return _topicId;
			}

		friend void MessengerService::addPublisher(MessagePublisher*);
		friend void MessengerService::removePublisher(MessagePublisher*);
	};

}
