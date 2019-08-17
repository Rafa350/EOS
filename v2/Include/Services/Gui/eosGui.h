#ifndef __eosGui__
#define __eosGui__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include <Services/Gui/eosGuiMessageQueue.h>
#include "System/Core/eosTask.h"


#ifndef OPT_GUI_ServicePriority
#define OPT_GUI_ServicePriority        TaskPriority::normal
#endif
#ifndef OPT_GUI_ServiceStack
#define OPT_GUI_ServiceStack           512
#endif


namespace eos {

	class Screen;
#ifdef OPT_GUI_TouchPad
	class GuiTouchPadService;
	struct TouchPadEventArgs;
#endif
#ifdef OPT_GUI_Keyboard
	class GuiKeyboardService;
#endif
#ifdef OPT_GUI_Selector
	class GuiSelectorService;
#endif


	struct GuiServiceInitInfo {
	};

	class GuiService: public Service {
		private:
			Screen *screen;
			GuiMessageQueue msgQueue;
#ifdef OPT_GUI_TouchPad
			GuiTouchPadService *touchPadService;
			bool touchPadPressed;
			int touchPadX;
			int touchPadY;
#endif

		public:
			GuiService(Application *application, const GuiServiceInitInfo *info);
			inline Screen* getScreen() const { return screen; }

		protected:
			void onInitialize() override;
			void onTask() override;

		private:
			void touchPadServiceNotify(TouchPadEventArgs *args);
	};
}


#endif // __eosGui__

