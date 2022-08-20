#pragma once
#ifndef __eosSerialDriver_IT__
#define __eosSerialDriver_IT__


#include "HTL/htlUART.h"
#include "System/eosCallbacks.h"


namespace eos {

	class SerialDriver_IT {
		public:
			enum class State {
				reset,
				ready,
				sending,
				receiving
			};
			enum class Event {
				completed,
				aborted
			};
			struct EventArgs {
				SerialDriver_IT *driver;
				Event event;
				void *param;
			};
    		using ICallback = ICallbackP1<const EventArgs&>;

		private:
			htl::UARTAdapter &_uart;
			State _state;
			const uint8_t *_data;
			unsigned _dataLength;
            ICallback *_callback;
            void *_callbackParam;

            void invokeCallback(Event event);
			void interruptHandler(htl::UARTEvent event);
			static void interruptHandler(htl::UARTEvent event, htl::UARTInterruptParam param);

		public:
			SerialDriver_IT(htl::UARTAdapter &uart);
			~SerialDriver_IT();

			void initialize();
			void deinitialize();

			inline bool isBusy() const { return _state != State::ready; }

			void setCallback(ICallback &callback, void *callbackParam);

			bool send(const uint8_t *data, unsigned dataLength);
			unsigned receive(uint8_t *data, unsigned dataSize);
	};
}


#endif // eosSerialDriver_IT__
