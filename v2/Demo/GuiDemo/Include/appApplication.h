#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"
#include "System/Core/eosCallbacks.h"
#include "Services/Gui/Visuals/eosPushButton.h"


namespace eos {

	class GuiService;
	class Panel;
}


namespace app {

	class LedService;

	class MyApplication: public eos::Application {
		private:
			typedef eos::CallbackP1<MyApplication, const eos::ButtonEventArgs&> ButtonEventCallback;

		private:
			LedService *ledService;
			eos::GuiService *guiService;

			eos::Panel *mainPanel;

			ButtonEventCallback buttonEventCallback;

		protected:
			void onInitialize() override;

			eos::Panel *createMainPanel();
			void buttonEventHandler(const eos::ButtonEventArgs &args);

		public :
			MyApplication();
	};

}

#endif
