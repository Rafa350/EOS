#ifndef __eosGuiTouchPad__
#define __eosGuiTouchPad__


// EOS includes
//
#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "Services/eosService.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"


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

	class GuiTouchPadService: public Service {
		private:
        	typedef ICallbackP1<TouchPadEventArgs*> TouchPadEvent;

		private:
    		ITouchPadDriver *touchDriver;
        	TouchPadEvent *evNotify;
        	int oldX;
        	int oldY;
        	int oldPressed;

		public:
			GuiTouchPadService(Application *application);
			~GuiTouchPadService();

			template <class cls>
            void setNotifyEvent(cls *instance, void (cls::*method)(TouchPadEventArgs *args)) {
                evNotify = new CallbackP1<cls, TouchPadEventArgs*>(instance, method);
            }

		protected:
			void onInitialize();
			void onTask();
	};
}


#endif // __eosGuiTouchPad__
