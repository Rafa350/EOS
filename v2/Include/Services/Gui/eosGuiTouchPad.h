#ifndef __eosGuiTouchPad__
#define __eosGuiTouchPad__


// EOS includes
//
#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "Services/eosService.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"


namespace eos {

	struct TouchPadEventArgs {
		bool isPressed;
		int x;
		int y;
	};

	class GuiTouchPadService: public Service {
		private:
        	typedef ICallbackP1<TouchPadEventArgs*> TouchPadEvent;

		private:
    		ITouchPadDriver *touchDriver;
        	TouchPadEvent *evNotify;

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
