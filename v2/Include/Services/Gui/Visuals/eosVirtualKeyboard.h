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
		private:
			typedef CallbackP1<VirtualKeyboard, const ButtonBase::EventArgs&> ButtonEventCallback;

		private:
			ButtonEventCallback buttonEventCallback;

		private:
			PushButton *createPushButton(const String &text, const Size &size);
			void buttonEventHandler(const ButtonBase::EventArgs &args);

		protected:
			void initializePanel();

		public:
			VirtualKeyboard();
	};

	class VirtualKeyboardTemplate: public ITemplate {
		private:
			VirtualKeyboard *visual;

		private:
			PushButton *createPushButton(const String &text, const Size &size);

		public:
			VirtualKeyboardTemplate(VirtualKeyboard *visual);
			void applyTemplate() override;
	};
}


#endif //__eosVirtualKbd__
