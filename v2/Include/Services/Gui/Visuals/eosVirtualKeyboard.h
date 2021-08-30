#ifndef __eosVirtualKbd__
#define __eosVirtualKbd__


#include "eos.h"
#include "Services/Gui/eosTemplate.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "System/eosEvents.h"


namespace eos {

	class Size;
	class String;
	class VirtualKeyboard;

	struct VirtualKeyboardEventArgs: public VisualEventArgs {
		KeyCode keyCode;

		inline VirtualKeyboardEventArgs(VirtualKeyboard* virtualKeyboard, KeyCode keyCode):
			VisualEventArgs((Visual*)virtualKeyboard),
			keyCode(keyCode) {
		}
	};

	typedef ICallbackP1<const VirtualKeyboardEventArgs&> IVirtualKeyboardEventCallback;

	template <typename C>
	class VirtualKeyboardEventCallback: public CallbackP1<C, const VirtualKeyboardEventArgs&> {
		public:
			using M = typename CallbackP1<C, const VirtualKeyboardEventArgs&>::Method;
		public:
			inline VirtualKeyboardEventCallback(C* instance, M handler):
				CallbackP1<C, const VirtualKeyboardEventArgs&>(instance, handler) {
			}
	};

	class VirtualKeyboard: public Panel {

		private:
			const IVirtualKeyboardEventCallback* _virtualKeyboardEventCallback;
			ButtonEventCallback<VirtualKeyboard> _buttonClickEventCallback;

		private:
			void buttonClickEventHandler(const ButtonEventArgs& args);

		protected:
			void initializePanel();

		public:
			VirtualKeyboard();

			inline const IButtonEventCallback* getButtonClickEventCallback() const {
				return &_buttonClickEventCallback;
			}

			inline void setVirtualKeyboardEventCallback(const IVirtualKeyboardEventCallback* callback) {
				_virtualKeyboardEventCallback = callback;
			}
	};

	class VirtualKeyboardTemplate: public ITemplate {
		private:
			VirtualKeyboard* _visual;

		private:
			PushButton* createPushButton(const String& text, const Size& size);

		public:
			VirtualKeyboardTemplate(VirtualKeyboard* visual);
			void applyTemplate() override;
	};
}


#endif //__eosVirtualKbd__
