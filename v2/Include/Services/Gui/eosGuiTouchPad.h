#ifndef __eosGuiTouchPad__
#define __eosGuiTouchPad__


// EOS includes
//
#include "eos.h"
#include "System/Core/eosCallbacks.h"
#include "Services/eosService.h"
#include "System/Core/eosTask.h"


namespace eos {

	class Application;

	typedef struct {
	} TouchPadEventArgs;

	class GuiTouchPadService: public Service {
		private:
        	typedef ICallbackP1<TouchPadEventArgs*> ITouchPadEvent;

		private:
        	ITouchPadEvent *evNotify;

		public:
			GuiTouchPadService(Application *application);
			~GuiTouchPadService();
			void initialize();

			template <class cls>
            void setNotifyEvent(cls *instance, void (cls::*method)(TouchPadEventArgs *args)) {
                evNotify = new CallbackP1<cls, TouchPadEventArgs*>(instance, method);
            }

		private:
			void run(Task *task);
	};
}


#endif // __eosGuiTouchPad__
