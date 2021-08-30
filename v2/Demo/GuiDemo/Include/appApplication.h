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
	class Visual;
	class Panel;
}


namespace app {

	class LedService;

	class MyApplication: public eos::Application {
		private:
			LedService *_ledService;
			eos::GuiService *_guiService;

			eos::ButtonEventCallback<MyApplication> _buttonEventCallback;
			eos::VirtualKeyboardEventCallback<MyApplication> _virtualKeyboardEventCallback;

		protected:
			void onInitialize() override;

			void createMainPanel();
			eos::Visual* createKeyboardPanel();
			void buttonEventHandler(const eos::ButtonEventArgs& args);
			void virtualKeyboardEventHandler(const eos::VirtualKeyboardEventArgs& args);

		public :
			MyApplication();
	};

}

#endif
