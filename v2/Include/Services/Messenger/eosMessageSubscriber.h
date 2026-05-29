#pragma once


#include "eos.h"
#include "Services/Messenger/eosMessengerService.h"


namespace eos {

	struct MessageSubscriberEventArgs {
		TopicID topicId;
		void *payload;
	};
	using IMessageSubscriberEvent = eos::ICallbackP2<MessageSubscriber*, MessageSubscriberEventArgs*>;
	template <typename Instance_> using MessageSubscriberEvent = eos::CallbackP2<Instance_, MessageSubscriber*, MessageSubscriberEventArgs*>;

	class MessageSubscriber: public MessageSubscriberListNode {
		private:
			MessengerService *_service;
			TopicID const _topicId;
			IMessageSubscriberEvent * const _event;

		public:
			MessageSubscriber(TopicID topicId, IMessageSubscriberEvent &event);

			void dispatch(void *payload);

			inline TopicID getTopicId() const {
				return _topicId;
			}

			inline MessengerService *getService() const {
				return _service;
			}

		friend MessengerService;
	};
}
