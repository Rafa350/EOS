#pragma once
#ifndef __eosMsgBrokerService__
#define __eosMsgBrokerService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Core/eosQueue.h"


namespace eos {

	class MsgPublisher;
	class MsgSubscriber;

    using MsgPublisherList = IntrusiveForwardList<MsgPublisher, 0>;
    using MsgPublisherListNode = IntrusiveForwardListNode<MsgPublisher, 0>;

    using MsgSubscriberList = IntrusiveForwardList<MsgSubscriber, 0>;
    using MsgSubscriberListNode = IntrusiveForwardListNode<MsgSubscriber, 0>;

    using MsgTopic = uint32_t;
    using MsgPayload = void*;

	class MsgBrokerService final: public Service {
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
    					MsgPublisher *publisher;
    				} addPublisher;
    				struct {
    					MsgSubscriber *subscriber;
    				} addSubscriber;
    				struct {
    					MsgPublisher *publisher;
    					MsgTopic topic;
    					MsgPayload payload;
    				} publish;
    			};
    		};
    		using ActionQueue = eos::Queue<Action>;

		private:
    		MsgPublisherList _publisherList;
    		MsgSubscriberList _subscriberList;
    		ActionQueue _actionQueue;

		private:
    		void processAddPublisher(MsgPublisher *publisher);
    		void processAddSubscriber(MsgSubscriber *subscriber);
    		void processPublish(MsgPublisher *publisher, MsgTopic topic, MsgPayload payload);

    	protected:
            void onExecute() override;

        public:
            MsgBrokerService();

            bool addPublisher(MsgPublisher *publisher, uint32_t blockTime);
            bool addSubscriber(MsgSubscriber *subscriber, uint32_t blockTime);
            bool publish(MsgPublisher *publisher, MsgTopic topic, MsgPayload payload, uint32_t blockTime);

        friend void __link(MsgBrokerService *service, MsgPublisher *publisher);
        friend void __link(MsgBrokerService *service, MsgSubscriber *subscriber);
    };
}


#endif // __eosMsgBrokerService__
