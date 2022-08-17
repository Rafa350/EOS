#ifndef __eosUARTService__
#define __eosUARTService__


/// EOS includes
//
#include "eos.h"
#include "HTL/htlUART.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosSemaphore.h"
#include "Services/eosService.h"


namespace eos {

	class UARTService: public Service {
		public:
			enum class Event {
				transmissionFinished,
				receptionFinished
			};
			struct EventArgs {
				Event event;
				uint8_t *buffer;
				unsigned count;
			};
			typedef ICallbackP1<const EventArgs&> IEventCallback;

		private:
			htl::UARTAdapterBase &_uart;
			uint8_t *_txBuffer;
			unsigned _txLength;
			unsigned _txCount;
			uint8_t *_rxBuffer;
			unsigned _rxSize;
			unsigned _rxCount;
			Semaphore _txPending;
			Semaphore _rxPending;

		public:
			UARTService(Application *application);
			virtual ~UARTService();

			void onInitialize() override;
			void onTerminate() override;
			void onTask(Task *task) override;

			unsigned send(uint8_t *data, unsigned length, unsigned blockTime);
			unsigned receive(uint8_t *data, unsigned size, unsigned blockTime);

			void uartInterruptFunction(htl::UARTEvent event);
			static void uartInterruptFunction(htl::UARTEvent event, htl::UARTInterruptParam param);
	};
}


#endif // __eosUARTService__
