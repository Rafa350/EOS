#ifndef __eosUARTService__
#define __eosUARTService__


/// EOS includes
//
#include "eos.h"
#include "HAL/halUART.h"
#include "System/Core/eosQueue.h"
#include "System/Core/eosSemaphore.h"
#include "Services/eosService.h"


namespace eos {

	class UARTService: public Service {
		private:
			struct Command {
				uint8_t* data;
				unsigned length;
			};
			typedef Queue<Command> CommandQueue;
		public:
			struct InitParams {
				UARTHandler hUART;
			};

		private:
			UARTHandler hUART;
			CommandQueue commandQueue;
			Semaphore txPending;
			uint8_t* txData;
			unsigned txLength;
			unsigned txCount;

		public:
			UARTService(Application* application, const InitParams& initParams);
			virtual ~UARTService();

			void onInitialize() override;
			void onTerminate() override;
			void onTask() override;

			bool send(uint8_t* data, unsigned length, unsigned blockTime);

			void uartInterruptFunction(uint32_t event);
            static void uartInterruptFunction(UARTHandler handler, void* params, uint32_t event);
	};
}


#endif // __eosUARTService__
