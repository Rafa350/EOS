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

	template <typename Id_, typename Args_>
	class EventRaiser {

		static_assert(std::is_enum_v<Id_>);

		public:
			using IEvent = ICallbackP1<const Args_&>;
			template <typename Instance_> using Event = CallbackP1<Instance_, const Args_&>;

		private:
			IEvent *_event;
			uint32_t _enabled;

		public:
			EventRaiser() :
				_event {nullptr},
				_enabled {0} {
			}

			void raise(Id_ id, const Args_ &args) const {
				if (isEnabled(id))
					_event->execute(args);
			}

			inline bool isEnabled() const {
				return _enabled & 0x80000000;
			}

			inline bool isEnabled(Id_ id) const {
				return isEnabled() && (_enabled & ~(1 << unsigned(id)));
			}

			void set(IEvent &event) {
				_event = &event;
				_enabled = 0x80000000;
			}

			void set(IEvent &event, bool enabled) {
				_event = &event;
				_enabled = enabled ? 0x80000000 : 0x00000000;
			}

			void set(IEvent &event, bool enabled, bool enabledAll) {
				_event = &event;
				_enabled = enabled ? (enabledAll ? 0xFFFFFFFF : 0x80000000) : 0x00000000;
			}

			inline void enable() {
				if (_event != nullptr)
					_enabled |= 0x80000000;
			}

			inline void enableAll() {
				if (_event != nullptr)
					_enabled = 0xFFFFFFFF;
			}

			inline void disable() {
				_enabled &= ~0x80000000;
			}

			inline void disableAll() {
				_enabled = 0x00000000;
			}

			inline void enable(Id_ id) {
				_enabled |= 1 << unsigned(id);
			}

			inline void disable(Id_ id) {
				_enabled &= ~(1 << unsigned(id));
			}
	};
}


#endif // __eosEvents__

