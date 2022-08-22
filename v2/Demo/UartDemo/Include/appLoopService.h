#ifndef __appLoop__
#define __appLoop__


#include "eos.h"
#include "Services/eosAppLoopService.h"
#include "System/Core/eosSemaphore.h"
#include "Controllers/Serial/eosSerialDriver_IT.h"


namespace app {

	class MyAppLoopService: public eos::AppLoopService {
		private:
        	using TxCompletedEventCallback = CallbackP1<MyAppLoopService, const SerialDriver_IT::TxCompletedEventArgs&>;
        	using RxCompletedEventCallback = CallbackP1<MyAppLoopService, const SerialDriver_IT::RxCompletedEventArgs&>;

		private:
			SerialDriver_IT *_serial;
			TxCompletedEventCallback _txCompletedCallback;
			RxCompletedEventCallback _rxCompletedCallback;
			unsigned _rxDataCount;
			Semaphore _txCompleted;
			Semaphore _rxCompleted;

		private:
            void txCompletedEventHandler(const SerialDriver_IT::TxCompletedEventArgs &args);
            void rxCompletedEventHandler(const SerialDriver_IT::RxCompletedEventArgs &args);

		protected:
			void onSetup() override;
			void onLoop() override;

		public:
			MyAppLoopService(eos::Application *application);
	};
}


#endif // __appLoop__

