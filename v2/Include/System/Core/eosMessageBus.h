#pragma once
#ifndef __eosMessageBus__
#define __eosMessageBus__


#include "eos.h"
#include "OSAL/osalMutex.h"
#include "System/eosEvents.h"
#include <System/Collections/eosIntrusiveForwardList.h>


namespace eos {

	template <typename Message_>
	class MessageBus {
		public:
			using SubscriptionEventRaiser = EventRaiser<MessageBus, Message_>;
			using ISubscriptionEvent = typename SubscriptionEventRaiser::IEvent;
			template <typename Instance_> using SubscriptionEvent = typename SubscriptionEventRaiser::Event<Instance_>;

		private:
			class Subscription;
		    using SubscriptionList = IntrusiveForwardList<Subscription, 0>;
		    using SubscriptionListNode = IntrusiveForwardListNode<Subscription, 0>;

		    class Subscription: public SubscriptionListNode {
		    	private:
				    SubscriptionEventRaiser _er;

		    	public:
				    Subscription(ISubscriptionEvent &event, bool enabled) {
				    	_er.set(event, enabled);
				    }
				    void publish(MessageBus * const sender, Message_ &message) {
				    	_er(sender, &message);
				    }
			};

		private:
		    SubscriptionList _subscriptions;
			HMutex _mutex;

		public:
			MessageBus() :
				_mutex {osalMutexCreate()} {
			}

			/// \brief  Afegeix un subscriptor a la llista.
			/// \param  event: Event de la subscripcio..
		    /// \param  enabled: Trus si l'event esta habilitat.
			///
			void subscribe(ISubscriptionEvent &event, bool enabled) {

				auto subscription = new Subscription(event, enabled);
				_subscriptions.pushFront(subscription);
			}

			/// \brief  Publica un missatge i el distribueix immediatament a tots els
			///         subscriptors.
			/// \param  message: El missatge a publicar.
			/// \param  waitIme: El tempsaa maxim d'espera.
			/// \return True si tot es correcte, false en cas d'error o timeout.
			///
			bool publish(Message_ &message, unsigned waitTime) {

				bool result = false;

				if (osalMutexWait(_mutex, waitTime)) {
					for (auto subscription: _subscriptions)
						subscription->publish(this, message);
					osalMutexRelease(_mutex);
				}

				return result;
			}
	};
}


#endif // __eosMessageBus__
