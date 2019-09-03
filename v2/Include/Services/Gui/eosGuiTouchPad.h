#ifndef __eosGuiTouchPad__
#define __eosGuiTouchPad__


// EOS includes
//
#include "eos.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "HAL/halEXTI.h"
#include "Services/eosService.h"
#include "System/Core/eosCallbacks.h"
#include "System/Core/eosSemaphore.h"


#ifndef OPT_GUI_TouchPadServicePrority
#define OPT_GUI_TouchPadServicePriority     TaskPriority::normal
#endif
#ifndef OPT_GUI_TouchPadServiceStack
#define OPT_GUI_TouchPadServiceStack        512
#endif


namespace eos {

	enum class TouchPadEventType {
		press,
		release,
		move
	};

	struct TouchPadEventArgs {
		TouchPadEventType event;
		int x;
		int y;
	};

	struct GuiTouchPadServiceConfiguration {
		ServiceConfiguration serviceConfiguration;
	};

	class GuiTouchPadService final: public Service {
		private:
        	typedef ICallbackP1<const TouchPadEventArgs&> TouchPadEvent;

		private:
    		ITouchPadDriver *touchDriver;
        	TouchPadEvent *evNotify;
        	BinarySemaphore lock;
        	int oldX;
        	int oldY;
        	int oldPressed;

		public:
			GuiTouchPadService(Application *application);
			GuiTouchPadService(Application *pApplication, const GuiTouchPadServiceConfiguration &configuration);
			~GuiTouchPadService();

			template <class cls>
            void setNotifyEvent(cls *instance, void (cls::*method)(const TouchPadEventArgs &args)) {
                evNotify = new CallbackP1<cls, const TouchPadEventArgs&>(instance, method);
            }

		protected:
			void onInitialize();
			void onTask();

		private:
			void interruptHandler();
			static void interruptHandler(EXTILine line, void *pParam);
	};
}


#endif // __eosGuiTouchPad__
