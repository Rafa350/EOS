#ifndef __eosGuiService__
#define __eosGuiService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosTask.h"


#if eosGuiService_TouchPadEnabled
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
#if eosGuiService_KeyboardEnabled
	class GuiKeyboardService;
#endif
#if eosGuiService_SelectorEnabled
	class GuiSelectorService;
#endif


	class GuiService final: public Service {
		private:
			typedef CallbackP1<GuiService, const TouchPadService::EventArgs&> TouchPadEventCallback;

			Screen* _screen;
			Visual* _active;
			MsgQueue* _msgQueue;
#if eosGuiService_KeyboardEnabled
			KeyboardService* _keyboardService;
#endif
#if eosGuiService_SelectorEnabled
			SelectorService* _selectorService;
#endif
#if eosGuiService_TouchPadEnabled
			TouchPadEventCallback _touchPadEventCallback;
			TouchPadService* _touchPadService;
			Visual* _touchPadTarget;
#endif

		public:
			GuiService(Application* application);
			inline Screen* getScreen() const { return _screen; }
			inline Visual* getActiveVisual() const { return _active; }
			Visual* getVisualAt(const Point &position) const;
			void setActiveVisual(Visual *pVisual);

		protected:
			void onInitialize() override;
			void onTask(Task *task) override;

		private:
#if eosGuiService_TouchPadEnabled
			void touchPadEventHandler(const TouchPadService::EventArgs& args);
#endif
	};
}


#endif // __eosGuiService__

