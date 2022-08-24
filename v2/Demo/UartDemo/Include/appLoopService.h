#ifndef __appLoop__
#define __appLoop__


#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "System/Core/eosSemaphore.h"
#include "Controllers/Serial/eosAsyncSerialDriver_UART.h"


namespace app {

	class MyAppLoopService: public eos::AppLoopService {
		private:
        	using TxCompletedEventCallback = CallbackP1<MyAppLoopService, const AsyncSerialDriver::TxCompletedEventArgs&>;
        	using RxCompletedEventCallback = CallbackP1<MyAppLoopService, const AsyncSerialDriver::RxCompletedEventArgs&>;

		private:
			AsyncSerialDriver *_serial;
			TxCompletedEventCallback _txCompletedCallback;
			RxCompletedEventCallback _rxCompletedCallback;
			unsigned _rxDataCount;
			Semaphore _txCompleted;
			Semaphore _rxCompleted;

		private:
            void txCompletedEventHandler(const AsyncSerialDriver::TxCompletedEventArgs &args);
            void rxCompletedEventHandler(const AsyncSerialDriver::RxCompletedEventArgs &args);

		protected:
			void onSetup() override;
			void onLoop() override;

		public:
			MyAppLoopService(eos::Application *application);
	};
}


#endif // __appLoop__

