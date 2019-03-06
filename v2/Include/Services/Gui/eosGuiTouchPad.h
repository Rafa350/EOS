#ifndef __eosGuiTouchPad__
#define __eosGuiTouchPad__


// EOS includes
//
#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "System/Core/eosTask.h"
#include "Services/eosService.h"
#include "Controllers/TouchPad/eosTouchPad.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"

// Standard includes
#include <stdint.h>


namespace eos {

	class Application;

	typedef struct {
		int16_t x[TOUCHPAD_MAX_POINTS];
		int16_t y[TOUCHPAD_MAX_POINTS];
	} TouchPadEventArgs;

	class GuiTouchPadService: public Service {
		private:
        	typedef ICallbackP1<TouchPadEventArgs*> TouchPadEvent;

		private:
    		ITouchPadDriver *touchDriver;
            TouchPad *touch;
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
