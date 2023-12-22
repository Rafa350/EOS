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
        	using TxCompletedEvent = eos::CallbackP1<MainService, const eos::AsyncSerialDriver::TxCompletedEventArgs&>;
        	using RxCompletedEvent = eos::CallbackP1<MainService, const eos::AsyncSerialDriver::RxCompletedEventArgs&>;

        	static constexpr htl::UARTWordBits _wordBits = htl::UARTWordBits::_8;
        	static constexpr htl::UARTStopBits _stopBits = htl::UARTStopBits::_1;
        	static constexpr htl::UARTParity _parity = htl::UARTParity::none;
        	static constexpr htl::UARTBaudMode _baudMode = htl::UARTBaudMode::_9600;

        	static constexpr htl::INTVector _vector = htl::UARTTrait<COM_UART::channel>::vector;
        	static constexpr htl::INTPriority _priority = htl::INTPriority::_5;
        	static constexpr htl::INTSubPriority _subPriority = htl::INTSubPriority::_0;

		private:
			eos::AsyncSerialDriver *_serial;

			TxCompletedEvent _txCompletedEvent;
			eos::Semaphore _txCompleted;

			RxCompletedEvent _rxCompletedEvent;
			eos::Semaphore _rxCompleted;
			unsigned _rxDataCount;

		private:
            void txCompletedEventHandler(const eos::AsyncSerialDriver::TxCompletedEventArgs &args);
            void rxCompletedEventHandler(const eos::AsyncSerialDriver::RxCompletedEventArgs &args);

		protected:
			bool onTaskStart() override;
			bool onTask() override;

		public:
			MainService();
	};
}


#endif // __appMainService__

