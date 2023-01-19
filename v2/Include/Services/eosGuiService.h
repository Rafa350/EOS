#ifndef __eosGuiService__
#define __eosGuiService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosTask.h"


#if eosGuiService_TouchpadEnabled
#include "Services/eosTouchpadService.h"
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
			static constexpr uint16_t _displayWidth = DISPLAY_WIDTH;
			static constexpr uint16_t _displayHeight = DISPLAY_HEIGHT;
			static constexpr uint32_t _displayBuffer = DISPLAY_BUFFER;

			typedef CallbackP1<GuiService, const TouchpadService::EventArgs&> TouchpadEventCallback;

			Screen* _screen;
			Visual* _active;
			Visual* _focus;
			MsgQueue& _msgQueue;
#if eosGuiService_KeyboardEnabled
			KeyboardService* _keyboardService;
#endif
#if eosGuiService_SelectorEnabled
			SelectorService* _selectorService;
#endif
#if eosGuiService_TouchpadEnabled
			TouchpadEventCallback _touchpadEventCallback;
			TouchpadService* _touchpadService;
			Visual* _touchpadTarget;
#endif

		public:
			GuiService(Application* application);
			inline Screen* getScreen() const { return _screen; }
			inline Visual* getActive() const { return _active; }
			inline Visual* getFocus() const { return _focus; }
			Visual *getVisualAt(const Point& position) const;

			void setActive(Visual* visual);
			void setFocus(Visual* visual);

		protected:
			void onInitialize() override;
			void onTask() override;

		private:
#if eosGuiService_TouchpadEnabled
			void touchpadEventHandler(const TouchpadService::EventArgs &args);
#endif
	};
}


#endif // __eosGuiService__

