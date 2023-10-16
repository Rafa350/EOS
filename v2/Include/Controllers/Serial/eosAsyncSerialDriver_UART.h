#pragma once
#ifndef __eosAsyncSerialDriver_UART__
#define __eosAsyncSerialDriver_UART__


#include "Controllers/Serial/eosAsyncSerialDriver.h"
#include "HTL/htlUART.h"
#include "System/Core/eosTask.h"


namespace eos {

	class AsyncSerialDriver_UART final: public AsyncSerialDriver {
		private:
			using MyTaskCallback = TaskCallback<AsyncSerialDriver_UART>;
		private:
			htl::uart::UARTDeviceHandler _hUART;
			htl::uart::NotifyEvent<AsyncSerialDriver_UART> _uartNotifyEvent;
			MyTaskCallback _taskCallback;
			//Task _task;
		private:
			void initializeImpl() override;
			void deinitializeImpl() override;
			bool transmitImpl(const uint8_t *data, int dataLength) override;
			bool receiveImpl(uint8_t *data, int dataSize) override;
			void uartNotifyEventHandler(htl::uart::UARTDevice *sender, htl::uart::NotifyEventArgs &args);
			void taskCallbackHandler(const TaskCallbackArgs &args);

		public:
			AsyncSerialDriver_UART(htl::uart::UARTDeviceHandler hUART);
	};
}


#endif // eosAsyncSerialDriver_UART__
