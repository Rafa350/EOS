#ifndef __eosUARTService__
#define __eosUARTService__


/// EOS includes
//
#include "eos.h"
#include "HAL/halUART.h"
#include "System/Core/eosSemaphore.h"
#include "Services/eosService.h"


namespace eos {

	class UARTService: public Service {
		public:
			struct InitializeInfo {
				UARTHandler hUART;
			};

		private:
			UARTHandler hUART;
			uint8_t *txBuffer;
			unsigned txLength;
			unsigned txCount;
			uint8_t *rxBuffer;
			unsigned rxSize;
			unsigned rxCount;
			Semaphore txPending;
			Semaphore rxPending;

		public:
			UARTService(Application* application, const InitializeInfo& initializeInfo);
			virtual ~UARTService();

			void onInitialize() override;
			void onTerminate() override;
			void onTask(Task *task) override;

			unsigned send(uint8_t* data, unsigned length, unsigned blockTime);
			unsigned receive(uint8_t* data, unsigned size, unsigned blockTime);

			void uartInterruptFunction(uint32_t event);
            static void uartInterruptFunction(UARTHandler handler, void* params, uint32_t event);
	};
}


#endif // __eosUARTService__
