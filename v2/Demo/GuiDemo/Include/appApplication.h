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
			LedService *ledService;
			eos::GuiService *guiService;

			eos::Panel *mainPanel;

			ButtonEventCallback buttonEventCallback;
			VirtualKeyboardEventCallback virtualKeyboardEventCallback;

		protected:
			void onInitialize() override;

			eos::Panel *createMainPanel();
			void buttonEventHandler(const eos::ButtonBase::EventArgs &args);
			void virtualKeyboardEventHandler(const eos::VirtualKeyboard::EventArgs &args);

		public :
			MyApplication();
	};

}

#endif
