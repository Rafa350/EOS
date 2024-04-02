#pragma once
#ifndef __eosAsyncSerialDriver_UART__
#define __eosAsyncSerialDriver_UART__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"
#include "System/Core/eosSemaphore.h"
#include "System/Core/eosTask.h"


namespace eos {

	class AsyncSerialDriver_UART: public AsyncSerialDriver {
	    public:
            using DevUART = htl::uart::UARTDevice;

	    private:
	        using UARTNotifyEvent = htl::uart::NotifyEvent<AsyncSerialDriver_UART>;
	        using UARTNotifyEventArgs = htl::uart::NotifyEventArgs;
            //using TaskEvent = TaskCallback<AsyncSerialDriver_UART>;

		protected:
			DevUART * const _devUART;

		private:
			UARTNotifyEvent _uartNotifyEvent;
            /*TaskEvent _taskEvent;
            Task _task;
            Semaphore _taskLock;*/

		private:
			void initializeImpl() override;
			void deinitializeImpl() override;

			void uartNotifyEventHandler(UARTNotifyEventArgs &args);
            void taskEventHandler(const TaskCallbackArgs &args);

		protected:
            bool startTxImpl(const uint8_t *buffer, unsigned length) override;
            bool startRxImpl(uint8_t *buffer, unsigned bufferSize) override;

		public:
			AsyncSerialDriver_UART(DevUART *devUART);
	};
}


#endif // __eosAsyncSerialDriver_UART__
