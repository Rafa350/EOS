#ifndef __eosTouchPadService__
#define __eosTouchPadService__


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

	struct TouchPadServiceConfiguration {
		ServiceConfiguration serviceConfiguration;
	};

	class TouchPadService final: public Service {
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
			TouchPadService(Application *application);
			TouchPadService(Application *pApplication, const TouchPadServiceConfiguration &configuration);

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


#endif // __eosTouchPadService__
