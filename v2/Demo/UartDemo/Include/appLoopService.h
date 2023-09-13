#ifndef __appLoop__
#define __appLoop__


#include "eos.h"
#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlUART.h"
#include "HTL/htlINT.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosSemaphore.h"


namespace app {

	class MyAppLoopService: public eos::Service {
		private:
        	using TxCompletedEventCallback = eos::CallbackP1<MyAppLoopService, const eos::AsyncSerialDriver::TxCompletedEventArgs&>;
        	using RxCompletedEventCallback = eos::CallbackP1<MyAppLoopService, const eos::AsyncSerialDriver::RxCompletedEventArgs&>;

        	static constexpr htl::UARTWordBits _wordBits = htl::UARTWordBits::_8;
        	static constexpr htl::UARTStopBits _stopBits = htl::UARTStopBits::_1;
        	static constexpr htl::UARTParity _parity = htl::UARTParity::none;
        	static constexpr htl::UARTBaudMode _baudMode = htl::UARTBaudMode::_9600;

        	static constexpr htl::INTVector _vector = htl::UARTTrait<COM_UART::channel>::vector;
        	static constexpr htl::INTPriority _priority = htl::INTPriority::_5;
        	static constexpr htl::INTSubPriority _subPriority = htl::INTSubPriority::_0;

		private:
			eos::AsyncSerialDriver *_serial;

			TxCompletedEventCallback _txCompletedCallback;
			eos::Semaphore _txCompleted;

			RxCompletedEventCallback _rxCompletedCallback;
			eos::Semaphore _rxCompleted;
			unsigned _rxDataCount;

		private:
            void txCompletedEventHandler(const eos::AsyncSerialDriver::TxCompletedEventArgs &args);
            void rxCompletedEventHandler(const eos::AsyncSerialDriver::RxCompletedEventArgs &args);

		protected:
			void onInitialize() override;
			void onTask() override;

		public:
			MyAppLoopService();
	};
}


#endif // __appLoop__

