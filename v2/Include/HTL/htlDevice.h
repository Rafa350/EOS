#pragma once


#include "eosCallbacks.h"


namespace htl {

	class Device {
		public:
			template <typename sender_, typename args_>
			using IEvent = eos::ICallbackP2<sender_*, args_*>;

			template <typename Instance_, typename sender_, typename args_>
			using Event = eos::CallbackP2<Instance_, sender_*, args_*>;

		protected:
			Device () = default;

		public:
			Device (const Device &) = delete;
			Device (const Device &&) = delete;
			Device & operator = (const Device &) = delete;
			Device & operator = (const Device &&) = delete;
			virtual ~Device () = default;
	};
}
