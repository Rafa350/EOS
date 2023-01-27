#ifndef __eosTouchPadService__
#define __eosTouchPadService__


// EOS includes
//
#include "eos.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "HTL/STM32/htlEXTI.h"
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
	class TouchpadService final: public Service {
		public:
			enum class EventType {
				press,
				release,
				move
			};

			struct EventArgs {
				EventType event;
				int x;
				int y;
			};

		private:
			using EXTI_INT = TOUCHPAD_INT_EXTI;
			typedef ICallbackP1<const EventArgs&> IEventCallback;

    		ITouchPadDriver *_touchDriver;
        	IEventCallback *_eventCallback;
        	Semaphore _lock;
        	int _oldX;
        	int _oldY;
        	int _oldPressed;

        	void interruptHandler();
			static void interruptHandler(htl::EXTIEvent event, htl::EXTIInterruptParam param);

		protected:
			void onInitialize() override;
			void onTask() override;

		public:
			TouchpadService();
			inline void setEventCallback(IEventCallback *callBack) { _eventCallback = callBack; }
	};
}


#endif // __eosTouchPadService__
