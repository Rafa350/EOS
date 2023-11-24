#pragma once
#ifndef __eosTouchPadService__
#define __eosTouchPadService__


// EOS includes
//
#include "eos.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "Controllers/TouchPad/Drivers/eosTouchPadDriver_FT5336.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosSemaphore.h"


// Prioritat d'execucio del servei
#ifndef eosTouchPadService_TaskPrority
#define eosTouchPadService_TaskPriority TaskPriority::normal
#endif

// Tamany del stack del servei
#ifndef eosTouchPadService_StackSize
#define eosTouchPadService_StackSize 512
#endif


namespace eos {

	/// \brief Clase que implementa un servei de control del touchpad
	///
	class TouchPadService final: public Service {
		public:
			enum class NotifyType {
				press,
				release,
				move
			};
			struct NotifyEventArgs {
				NotifyType notifyType;
				int16_t x;
				int16_t y;
			};
			using INotifyEvent = ICallbackP2<TouchPadService*, NotifyEventArgs&>;
			template <typename instance_> using NotifyEvent = CallbackP2<instance_, TouchPadService*, NotifyEventArgs&>;

		private:
    		TouchPadDriver_FT5336 *_touchDriver;
    		TouchPadEvent<TouchPadService> _touchPadEvent;
    		INotifyEvent *_notifyEvent;
    		bool _notifyEventEnabled;
        	Semaphore _lock;
        	int16_t _oldX;
        	int16_t _oldY;
        	bool _oldPressed;

		private:
        	void touchPadEventHandler(TouchPadDriver_FT5336 *sender);

		protected:
			void onInitialize() override;
			void onTask() override;

		public:
			TouchPadService();
			void setNotifyEvent(INotifyEvent &event, bool enabled = true);
	};
}


#endif // __eosTouchPadService__
