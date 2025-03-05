#ifndef __appMainService__
#define __appMainService__


#include "eos.h"
#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlUART.h"
#include "Services/eosService.h"
#include "System/Core/eosSemaphore.h"


namespace app {

	class MainService: public eos::Service {
		private:
        	using UARTNotifyEvent = htl::uart::NotifyEvent<MainService>;

		private:
        	UARTNotifyEvent _uartNotifyEvent;
        	eos::Semaphore _completed;

		private:
            void uartNotifyEventHandler(htl::uart::NotifyID notifyID, htl::uart::NotifyEventArgs * const args);

		protected:
			void onExecute() override;

		public:
			MainService();
	};
}


#endif // __appMainService__

