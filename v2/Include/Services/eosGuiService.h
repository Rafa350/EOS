#ifndef __eosGuiService__
#define __eosGuiService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosTask.h"


#ifdef OPT_GUI_TouchPad
#include "Services/eosTouchPadService.h"
#endif


// Prioritat d'execucio del servei
#ifndef eosGuiService_TaskPriority
#define eosGuiService_TaskPriority Task::Priority::normal
#endif

// Tamany del stack del servei
#ifndef eosGuiService_StackSize
#define eosGuiService_StackSize 512
#endif


namespace eos {

	class Screen;
	class Visual;
	class Point;
	class MsgQueue;
#ifdef OPT_GUI_Keyboard
	class GuiKeyboardService;
#endif
#ifdef OPT_GUI_Selector
	class GuiSelectorService;
#endif


	class GuiService final: public Service {
		public:
			struct Configuration {

				Configuration();
			};

		private:
			typedef CallbackP1<GuiService, const TouchPadService::EventArgs&> TouchPadEventCallback;

			Configuration cfg;
			Screen *screen;
			Visual *active;
			MsgQueue *msgQueue;
#ifdef OPT_GUI_Keyboard
			KeyboardService *keyboardService;
#endif
#ifdef OPT_GUI_Selector
			SelectorService *selectorService;
#endif
#ifdef OPT_GUI_TouchPad
			TouchPadEventCallback touchPadEventCallback;
			TouchPadService *touchPadService;
			Visual *touchPadTarget;
#endif

		public:
			GuiService(Application *application, const Configuration *cfg = nullptr);
			inline Screen* getScreen() const { return screen; }
			inline Visual* getActiveVisual() const { return active; }
			Visual *getVisualAt(const Point &position) const;
			void setActiveVisual(Visual *pVisual);

		protected:
			void onInitialize() override;
			void onTask() override;

		private:
#ifdef OPT_GUI_TouchPad
			void touchPadEventHandler(const TouchPadService::EventArgs &args);
#endif
	};
}


#endif // __eosGuiService__

