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
	class Visual;
	class Point;
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


	struct GuiServiceConfiguration {
		ServiceConfiguration serviceConfiguration;
	};

	class GuiService final: public Service {
		private:
			Screen *screen;
			Visual *active;
			GuiMessageQueue msgQueue;
#ifdef OPT_GUI_Keyboard
#endif
#ifdef OPT_GUI_Selector
#endif
#ifdef OPT_GUI_TouchPad
			GuiTouchPadService *touchPadService;
			Visual *touchPadTarget;
#endif

		public:
			GuiService(Application *application);
			GuiService(Application *application, const GuiServiceConfiguration &configuration);
			inline Screen* getRootVisual() const { return screen; }
			inline Visual* getActiveVisual() const { return active; }
			Visual *getVisualAt(const Point &position) const;
			void setActiveVisual(Visual *visual);

		protected:
			void onInitialize() override;
			void onTask() override;

		private:
#ifdef OPT_GUI_TouchPad
			void touchPadServiceNotify(const TouchPadEventArgs &args);
#endif
	};
}


#endif // __eosGui__

