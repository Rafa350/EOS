#ifndef __eosGuiTouchPad__
#define __eosGuiTouchPad__


// EOS includes
//
#include "eos.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "HAL/STM32/halEXTI.h"
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
        	typedef ICallbackP1<const TouchPadEventArgs&> IEventCallback;

		private:
    		ITouchPadDriver *touchDriver;
        	IEventCallback *pEventCallback;
        	BinarySemaphore lock;
        	int oldX;
        	int oldY;
        	int oldPressed;

		public:
			GuiTouchPadService(Application *application);
			GuiTouchPadService(Application *pApplication, const GuiTouchPadServiceConfiguration &configuration);
			~GuiTouchPadService();

			template <class cls>
			void setEventCallback(CallbackP1<cls, const TouchPadEventArgs&> *pCallBack) {
				pEventCallback = pCallBack;
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