#ifndef __eosKeyboardEvents__
#define __eosKeyboardEvents__


#include "eos.h"
#include "Services/Gui/Events/eosEvents.h"


namespace eos {

	struct KeyboardEventArgs: public EventArgs {
		KeyCode keyCode;
		KeyFlags keyFlags;
		char ch;

		inline KeyboardEventArgs(Visual* visual, KeyCode keyCode, KeyFlags keyFlags, char ch):
			EventArgs(visual),
			keyCode(keyCode),
			keyFlags(keyFlags),
			ch(ch) {
		}
	};

	typedef KeyboardEventArgs KeyboardPressEventArgs;
	typedef KeyboardEventArgs KeyboardReleaseEventArgs;

	typedef ICallbackP1<const KeyboardPressEventArgs&> IKeybopardPressEventCallback;
	typedef ICallbackP1<const KeyboardReleaseEventArgs&> IKeyboardReleaseEventCallback;

	template <typename C>
	class KeyboardPressEventCallback: public CallbackP1<C, const KeyboardPressEventArgs&> {
		public:
			using M = typename CallbackP1<C, const KeyboardPressEventArgs&>::Method;
		public:
			KeyboardPressEventCallback(C* instance, M handler):
				CallbackP1<C, const KeyboardPressEventArgs&>(instance, handler) {
			}
	};

	template <typename C>
	class KeyboardReleaseEventCallback: public CallbackP1<C, const KeyboardReleaseEventArgs&> {
		public:
			using M = typename CallbackP1<C, const KeyboardReleaseEventArgs&>::Method;
		public:
			KeyboardReleaseEventCallback(C* instance, M handler):
				CallbackP1<C, const KeyboardReleaseEventArgs&>(instance, handler) {
			}
	};
}


#endif // __eosKeyboardEvents__

