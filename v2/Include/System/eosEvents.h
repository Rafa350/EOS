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


	template <typename Id_, typename Args_>
	class NotifyEventRaiser {

		static_assert(std::is_enum_v<Id_>);

		public:
			using IEvent = ICallbackP2<Id_, Args_ * const>;
			template <typename Instance_> using Event = CallbackP2<Instance_, Id_, Args_ * const>;

		private:
			IEvent *_event;
			uint32_t _enabled;

		public:
			NotifyEventRaiser() :
				_event {nullptr},
				_enabled {0} {
			}

			void raise(Id_ id) const {
				if (isEnabled(id))
					_event->execute(id, nullptr);
			}

			void raise(Id_ id, Args_ * const args) const {
				if (isEnabled(id))
					_event->execute(id, args);
			}

			inline bool isEnabled() const {
				return _enabled & 0x80000000;
			}

			inline bool isEnabled(Id_ id) const {
				return isEnabled() && (_enabled & ~(1 << unsigned(id)));
			}

			void set(IEvent &event) {
				_event = &event;
				_enabled = 0xFFFFFFFF;
			}

			void set(IEvent &event, bool enabled) {
				_event = &event;
				_enabled = enabled ? 0xFFFFFFFF : 0x00000000;
			}

			void set(IEvent &event, bool enabled, bool enabledAll) {
				_event = &event;
				_enabled = enabled ? (enabledAll ? 0xFFFFFFFF : 0x80000000) : 0x00000000;
			}

			void enable() {
				if (_event != nullptr)
					_enabled |= 0x80000000;
			}

			void enableAll() {
				if (_event != nullptr)
					_enabled = 0xFFFFFFFF;
			}

			void disable() {
				_enabled &= 0x7FFFFFFF;
			}

			void disableAll() {
				_enabled = 0x00000000;
			}

			void enable(Id_ id) {
				_enabled |= 1 << unsigned(id);
			}

			void disable(Id_ id) {
				_enabled &= ~(1 << unsigned(id));
			}

			inline void operator() (Id_ id) {
				raise(id);
			}

			inline void operator() (Id_ id, Args_ * const args) {
				raise(id, args);
			}
	};
}


#endif // __eosEvents__

