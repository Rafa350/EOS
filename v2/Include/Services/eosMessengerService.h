#pragma once
#ifndef __eosMessengerService__
#define __eosMessengerService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosIntrusiveList.h"
#include "System/Core/eosQueue.h"


namespace eos {

    class Publisher;
    using PublisherList = IntrusiveForwardList<Publisher, 0>;
    using PublisherListNode = IntrusiveForwardListNode<Publisher, 0>;

    template <typename Message_>
    class Subscription;

    template <typename Message_>
    using SubscriptionList = IntrusiveForwardList<Subscription<Message_>, 0>;

    template <typename Message_>
    using SubscriptionListNode = IntrusiveForwardListNode<Subscription<Message_>, 0>;

    class Publisher: public PublisherListNode {
        protected:
            Publisher() = default;
	};

    template <typename Message_>
    class PublisherX final: public Publisher {
        private:
            using MessageQueue = Queue<Message_>;
        private:
            SubscriptionList<Message_> _subscriptions;
            MessageQueue _messageQueue;
        public:
            PublisherX(unsigned capacity):
                _messageQueue {capacity} {
            }
            inline void pusblish(const Message_ &message, unsigned blockTime) {
                _messageQueue.push(message, blockTime);
            }
            inline void pusblishISR(const Message_ &message) {
                _messageQueue.pushISR(message);
            }
            void subscribe(Subscription<Message_> *subscription) {
                _subscriptions.push_front(subscription);
            }
            void unsubscribe(Subscription<Message_> *subscription) {
            }
    };

    template <typename Message_>
    class Subscription: public SubscriptionListNode<Message_> {
        private:
            Publisher *_publisher;
    };

    class MessengerService final: public Service {
    	private:
			PublisherList _publishers;

    	protected:
            void onInitialize() override;
            void onTask() override;

        public:
            MessengerService();
            void addPublisher(Publisher *publisher);
            void removePublisher(Publisher *publisher);
    };
}


#endif // __eosMessengerService__
