#pragma once
#ifndef __eosEvents__
#define __eosEvents__


// EOS includes
//
#include "eos.h"
#include "System/eosCallbacks.h"

// STD includes
//
#include <type_traits>


namespace eos {

	template <typename Sender_, typename Args_>
	class EventRaiser {
		public:
			using IEvent = ICallbackP2<Sender_ * const, Args_ * const>;
			template <typename Instance_> using Event = CallbackP2<Instance_, Sender_ * const, Args_ * const>;

		private:
			IEvent *_event;
			bool _enabled;

		public:
			EventRaiser() :
				_event {nullptr},
				_enabled {false} {
			}

			EventRaiser(IEvent *event, bool enabled = true) :
				_event {event},
				_enabled {enabled} {
			}

			void raise(Sender_ * const sender, Args_ * const args) const {
				if (isEnabled())
					_event->execute(sender, args);
			}

			inline bool isEnabled() const {
				return _enabled;
			}

			void set(IEvent &event) {
				_event = &event;
				_enabled = true;
			}

			void set(IEvent &event, bool enabled) {
				_event = &event;
				_enabled = true;
			}

			void set(IEvent *event, bool enabled) {
				_event = event;
				_enabled = true;
			}

			inline void enable() {
				_enabled = _event != nullptr;
			}

			inline void disable() {
				_enabled = false;
			}

			inline void operator ()(Sender_ * const sender, Args_ * const args) {
				raise(sender, args);
			}
	};
}


#endif // __eosEvents__

