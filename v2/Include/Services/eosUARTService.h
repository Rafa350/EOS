#ifndef __eosUARTService__
#define __eosUARTService__


/// EOS includes
//
#include "eos.h"
#include "HAL/halUART.h"
#include "System/Core/eosSemaphore.h"
#include "System/Core/eosQueue.h"
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
			Semaphore semaphore;
			CommandQueue commandQueue;
			unsigned txCount;     // Nombre de bytes transmessos
			unsigned txLength;    // Longitut de les dades en bytes.
			uint8_t* txBuffer;    // Buffer de dades a transmetre

		public:
			UARTService(Application* application, const InitParams& initParams);
			virtual ~UARTService();

			void onInitialize() override;
			void onTerminate() override;
			void onTask() override;

			void send(uint8_t* data, unsigned length, unsigned blockTime);

			void uartInterruptFunction(uint32_t event);
            static void uartInterruptFunction(UARTHandler handler, void* params, uint32_t event);
	};
}


#endif // __eosUARTService__
