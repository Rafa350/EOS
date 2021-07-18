#ifndef __eosVirtualKbd__
#define __eosVirtualKbd__


#include "eos.h"
#include "Services/Gui/eosTemplate.h"
#include "Services/Gui/Visuals/eosPanel.h"
#include "Services/Gui/Visuals/eosPushButton.h"


namespace eos {

	class Size;
	class String;

	class VirtualKeyboard: public Panel {
		public:
			struct EventArgs {
				VirtualKeyboard* keyboard;
				KeyCode keyCode;
			};
			typedef ICallbackP1<const EventArgs&> IEventCallback;

		private:
			typedef CallbackP1<VirtualKeyboard, const ButtonBase::EventArgs&> ButtonEventCallback;

		private:
			const IEventCallback* _eventCallback;
			ButtonEventCallback _buttonEventCallback;

		private:
			void buttonEventHandler(const ButtonBase::EventArgs& args);

		protected:
			void initializePanel();

		public:
			VirtualKeyboard();

			inline const ButtonEventCallback* getButtonEventCallback() const {
				return &_buttonEventCallback;
			}

			inline void setEventCallback(const IEventCallback* callback) {
				_eventCallback = callback;
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
