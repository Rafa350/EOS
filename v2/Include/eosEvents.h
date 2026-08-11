#pragma once
#ifndef __eosEvents__
#define __eosEvents__


#include "eosCallbacks.h"


namespace eos {

	struct NullEventArgs {
	};

	template <typename Sender_, typename Args_>
	class EventRaiser final {
		public:
			using IEvent = ICallbackP2<Sender_*, Args_*>;
			template <typename Instance_> using Event = CallbackP2<Instance_, Sender_*, Args_*>;

		private:
			IEvent *_event;

		public:
			inline EventRaiser() :
				_event {nullptr} {
			}

			inline EventRaiser(IEvent &event) :
				_event {&event} {
			}

			inline void enable(IEvent &event) {
				_event = &event;
			}

			inline void disable() {
				_event = nullptr;
			}

			inline void raise(Sender_ *sender, Args_ *args) const {
				_event->execute(sender, args);
			}

			inline bool isEnabled() const {
				return _event != nullptr;
			}

			inline operator bool const () {
				return isEnabled();
			}

			inline void operator () (Sender_ *sender, Args_ *args) {
				raise(sender, args);
			}
	};
}


#endif // __eosEvents__
