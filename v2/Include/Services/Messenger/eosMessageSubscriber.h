#pragma once


#include "eos.h"
#include "Services/Messenger/eosMessengerService.h"


namespace eos {

	struct MessageSubscriberEventArgs {
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

			void dispatch(const MessagePayload &payload);

			inline TopicID getTopicId() const {
				return _topicId;
			}

		friend void MessengerService::addSubscriber(MessageSubscriber*);
		friend void MessengerService::removeSubscriber(MessageSubscriber*);
	};
}
