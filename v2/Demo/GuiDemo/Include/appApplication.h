#ifndef __appApplication__
#define __appApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosRTOSApplication.h"
#include "System/eosCallbacks.h"
#include "Services/eosTouchpadService.h"
#include "Services/Gui/Visuals/eosPushButton.h"
#include "Services/Gui/Visuals/eosVirtualKeyboard.h"


namespace eos {

	class GuiService;
	class Visual;
	class Panel;
}


namespace app {

	class LedService;

	class MyApplication: public eos::RTOSApplication {
		private:
			#if eosGuiService_TouchpadEnabled
				using TouchPadNotifyEvent = eos::TouchPadService::NotifyEvent<MyApplication>;
			#endif

		private:
			LedService *_ledService;
			eos::GuiService *_guiService;
			#if eosGuiService_KeyboardEnabled
				KeyboardService* _keyboardService;
			#endif
			#if eosGuiService_SelectorEnabled
				SelectorService* _selectorService;
			#endif
			#if eosGuiService_TouchpadEnabled
				eos::TouchPadService* _touchPadService;
				TouchPadNotifyEvent _touchPadNotifyEvent;
			#endif

			eos::ButtonEventCallback<MyApplication> _buttonEventCallback;
			eos::VirtualKeyboardEventCallback<MyApplication> _virtualKeyboardEventCallback;

		protected:
			void onInitialize() override;

			void createMainPanel();
			eos::Visual *createKeyboardPanel();
			eos::Visual *createDROPanel();
			void buttonEventHandler(const eos::ButtonEventArgs& args);
			void virtualKeyboardEventHandler(const eos::VirtualKeyboardEventArgs &args);
			#if eosGuiService_TouchpadEnabled
				void touchPadNotifyEventHandler(eos::TouchPadService *sender, eos::TouchPadService::NotifyEventArgs &args);
			#endif

		public :
			MyApplication();
	};

}

#endif
