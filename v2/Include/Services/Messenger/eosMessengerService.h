#pragma once


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Core/eosQueue.h"


namespace eos {

	class MessagePublisher;
	class MessageSubscriber;
	class MessengerService;

    using MessagePublisherList = IntrusiveForwardList<MessagePublisher, 0>;
    using MessagePublisherListNode = IntrusiveForwardListNode<MessagePublisher, 0>;

    using MessageSubscriberList = IntrusiveForwardList<MessageSubscriber, 0>;
    using MessageSubscriberListNode = IntrusiveForwardListNode<MessageSubscriber, 0>;

    using TopicID = uint32_t;
    using MessagePayload = void*;

	class MessengerService final: public Service {
		private:
    		struct QueueItem {
    			MessagePublisher *publisher;
				const MessagePayload *payload;
    		};
    		using Queue = eos::Queue<QueueItem>;

		private:
    		MessagePublisherList _publisherList;
    		MessageSubscriberList _subscriberList;
    		Queue _queue;

    	protected:
            void onExecute() override;

        public:
            MessengerService(uint32_t queueCapacity);

            void addPublisher(MessagePublisher *publisher);
            void addSubscriber(MessageSubscriber *subscriber);

            void removePublisher(MessagePublisher *publisher);
            void removeSubscriber(MessageSubscriber *subscriber);

            bool publish(MessagePublisher *publisher, const MessagePayload &payload, uint32_t blockTime);
    };

}
