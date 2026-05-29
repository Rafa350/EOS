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

			void publish(void *payload, uint32_t blockTime);

			inline MessengerService *getService() const {
				return _service;
			}

			inline TopicID getTopicId() const {
				return _topicId;
			}

		friend MessengerService;
	};

}
