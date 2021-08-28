#ifndef __eosTouchpadEvents__
#define __eosTouchpadEvents__


#include "eos.h"
#include "Services/Gui/Events/eosEvents.h"


namespace eos {

	struct TouchpadPressEventArgs: public EventArgs {
		Point position;

		inline TouchpadPressEventArgs(Visual* visual, const Point& position):
			EventArgs(visual),
			position(position) {
		}
	};

	struct TouchpadMoveEventArgs: public EventArgs {
		Point position;

		inline TouchpadMoveEventArgs(Visual* visual, const Point& position):
			EventArgs(visual),
			position(position) {
		}
	};

	typedef EventArgs TouchpadReleaseEventArgs;
	typedef EventArgs TouchpadEnterEventArgs;
	typedef EventArgs TouchpadLeaveEventArgs;

	typedef ICallbackP1<const TouchpadMoveEventArgs&> ITouchpadMoveEventCallback;
	typedef ICallbackP1<const TouchpadPressEventArgs&> ITouchpadPressEventCallback;
	typedef IEventCallback ITouchpadReleaseEventCallback;
	typedef IEventCallback ITouchpadEnterEventCallback;
	typedef IEventCallback ITouchpadLeaveEventCallback;

	template <typename C>
	class TouchpadMoveEventCallback: public CallbackP1<C, const TouchpadMoveEventArgs&> {
		public:
			using M = typename CallbackP1<C, const TouchpadMoveEventArgs&>::Method;
		public:
			TouchpadMoveEventCallback(C* instance, M handler):
				CallbackP1<C, const TouchpadMoveEventArgs&>(instance, handler) {
			}
	};

	template <typename C>
	class TouchpadPressEventCallback: public CallbackP1<C, const TouchpadPressEventArgs&> {
		public:
			using M = typename CallbackP1<C, const TouchpadPressEventArgs&>::Method;
		public:
			TouchpadPressEventCallback(C* instance, M handler):
				CallbackP1<C, const TouchpadPressEventArgs&>(instance, handler) {
			}
	};
}


#endif // __eosTouchpadEvents__

