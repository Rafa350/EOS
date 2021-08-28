#ifndef __eosEvents__
#define __eosEvents__


// EOS includes
//
#include "eos.h"
#include "System/eosCallbacks.h"


namespace eos {

	class Visual;

	struct EventArgs {
		Visual* sender;

		inline EventArgs(Visual* sender):
			sender(sender) {
		}
	};

	typedef ICallbackP1<const EventArgs&> IEventCallback;

	template <typename C>
	class EventCallback: public CallbackP1<C, const EventArgs&> {
		public:
			using M = typename CallbackP1<C, const EventArgs&>::Method;
		public:
			EventCallback(C* instance, M handler):
				CallbackP1<C, const EventArgs&>(instance, handler) {
			}
	};
}



#endif // __eosEvents__

