#ifndef __eosTouchPadService__
#define __eosTouchPadService__


// EOS includes
//
#include "eos.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "HAL/STM32/halEXTI.h"
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
			typedef ICallbackP1<const EventArgs&> IEventCallback;

    		ITouchPadDriver *_touchDriver;
        	IEventCallback *_eventCallback;
        	Semaphore _lock;
        	int _oldX;
        	int _oldY;
        	int _oldPressed;

        	void interruptHandler();
			static void interruptHandler(EXTILine line, void *param);

		protected:
			void onInitialize() override;
			void onTask(Task *task) override;

		public:
			TouchPadService(Application *application);
			inline void setEventCallback(IEventCallback *callBack) { _eventCallback = callBack; }
	};
}


#endif // __eosTouchPadService__
