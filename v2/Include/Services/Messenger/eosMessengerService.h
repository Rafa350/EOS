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

	class MessengerService final: public Service {
		private:
    		enum class ActionID {
    			addPublisher,
				addSubscriber,
				publish
    		};
    		struct Action {
    			ActionID actionId;
    			union {
					struct {
    					MessagePublisher *publisher;
    				} addPublisher;
    				struct {
    					MessageSubscriber *subscriber;
    				} addSubscriber;
    				struct {
    					MessagePublisher *publisher;
    					void *payload;
    				} publish;
    			};
    		};
    		using ActionQueue = eos::Queue<Action>;

		private:
    		MessagePublisherList _publisherList;
    		MessageSubscriberList _subscriberList;
    		ActionQueue _actionQueue;

		private:
    		void processAddPublisher(MessagePublisher *publisher);
    		void processAddSubscriber(MessageSubscriber *subscriber);
    		void processPublish(MessagePublisher *publisher, void *payload);

    	protected:
            void onExecute() override;

        public:
            MessengerService(uint32_t queueCapacity);

            void addPublisher(MessagePublisher *publisher, uint32_t blockTime);
            void addSubscriber(MessageSubscriber *subscriber, uint32_t blockTime);
            bool publish(MessagePublisher *publisher, void *payload, uint32_t blockTime);
    };

}
