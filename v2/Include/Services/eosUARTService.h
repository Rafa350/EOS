#ifndef __eosUARTService__
#define __eosUARTService__


/// EOS includes
//
#include "eos.h"
#include "HAL/halUART_ex.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosSemaphore.h"
#include "Services/eosService.h"


namespace eos {

	class UARTService: public Service {
		public:
			enum class Event {
				transmissionFiniched,
				receptionFinished
			};
			struct EventArgs {
				Event event;
				uint8_t *buffer;
				unsigned count;
			};
			typedef ICallbackP1<const EventArgs&> IEventCallback;
			struct Settings {
				halUARTHandler hUART;
				IEventCallback *eventCallback;
				void *eventParams;
			};

		private:
			UARTAttachedAdapter _uart;
			uint8_t *_txBuffer;
			unsigned _txLength;
			unsigned _txCount;
			uint8_t *_rxBuffer;
			unsigned _rxSize;
			unsigned _rxCount;
			Semaphore _txPending;
			Semaphore _rxPending;

		public:
			UARTService(Application *application, const Settings &settings);
			virtual ~UARTService();

			void onInitialize() override;
			void onTerminate() override;
			void onTask(Task *task) override;

			unsigned send(uint8_t* data, unsigned length, unsigned blockTime);
			unsigned receive(uint8_t* data, unsigned size, unsigned blockTime);

			void uartInterruptFunction(uint32_t event);
            static void uartInterruptFunction(halUARTHandler handler, void* params, uint32_t event);
	};
}


#endif // __eosUARTService__
