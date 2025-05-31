#ifndef __appMainService__
#define __appMainService__


#include "eos.h"
#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlUART.h"
#include "Services/eosService.h"
#include "System/Core/eosSemaphore.h"

#include "appConfig.h"


namespace app {

	class MainService: public eos::Service {
		private:
			using UARTNotifyID = htl::uart::NotifyID;
        	using UARTNotifyEvent = htl::uart::NotifyEvent<MainService>;
        	using UARTNotifyEventArgs = htl::uart::NotifyEventArgs;

		private:
        	hw::DevUART *_devUART;
        	UARTNotifyEvent _uartNotifyEvent;
        	eos::Semaphore _completed;

		private:
            void uartNotifyEventHandler(UARTNotifyID notifyID, UARTNotifyEventArgs * const args);

		protected:
			void onExecute() override;
			void testPollingMode();
			void testInterruptMode();
			void testDmaMode();

		public:
			MainService();
	};
}


#endif // __appMainService__

