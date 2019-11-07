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


// Nom del servei
#ifndef eosTouchPadService_ServiceName
#define eosTouchPadService_ServiceName "TouchPadService"
#endif

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
			struct Configuration {
				const ServiceConfiguration *serviceConfiguration;
			};

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

		private:
    		ITouchPadDriver *touchDriver;
        	IEventCallback *eventCallback;
        	BinarySemaphore lock;
        	int oldX;
        	int oldY;
        	int oldPressed;

		public:
			TouchPadService(Application *application);
			TouchPadService(Application *application, const Configuration *configuration);

			void setEventCallback(IEventCallback *callBack) { eventCallback = callBack; }

		protected:
			void onInitialize();
			void onTask();

		private:
			void interruptHandler();
			static void interruptHandler(EXTILine line, void *param);
	};
}


#endif // __eosTouchPadService__
