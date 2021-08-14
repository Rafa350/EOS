#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"
#include "System/eosCallbacks.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"


namespace eos {

	class GuiService;
	class Panel;
}


namespace app {

	class LedService;

	class MyApplication: public eos::Application {
		private:
			typedef eos::CallbackP1<MyApplication, const eos::ButtonBase::EventArgs&> ButtonEventCallback;
			typedef eos::CallbackP1<MyApplication, const eos::VirtualKeyboard::EventArgs&> VirtualKeyboardEventCallback;

		private:
			LedService *_ledService;
			eos::GuiService *_guiService;

			eos::Panel *_mainPanel;

			ButtonEventCallback _buttonEventCallback;
			VirtualKeyboardEventCallback _virtualKeyboardEventCallback;

		protected:
			void onInitialize() override;

			void createMainPanel();
			void buttonEventHandler(const eos::ButtonBase::EventArgs& args);
			void virtualKeyboardEventHandler(const eos::VirtualKeyboard::EventArgs& args);

		public :
			MyApplication();
	};

}

#endif
