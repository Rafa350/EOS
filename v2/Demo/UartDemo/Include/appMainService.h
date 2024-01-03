#ifndef __appMainService__
#define __appMainService__


#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlUART.h"
#include "HTL/htlINT.h"
#include "Services/eosService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosSemaphore.h"


namespace app {

	class MainService: public eos::Service {
		private:
        	using UARTNotifyEvent = htl::uart::NotifyEvent<MainService>;

		private:
        	UARTNotifyEvent _uartNotifyEvent;

		private:
            void uartNotifyEventHandler(const htl::uart::UARTDevice *uart, const htl::uart::NotifyEventArgs &args);

		protected:
			bool onTaskStart() override;
			bool onTask() override;

		public:
			MainService();
	};
}


#endif // __appMainService__

