#ifndef __STM32_eosUSBDevice__
#define __STM32_eosUSBDevice__


// EOS includes
//
#include "eos.h"
#include "Controllers/Usb/eosUSB.h"
#include "HAL/halUSB.h"


namespace eos {

	class UsbDevice: public UsbBase {
		private:
			USBPort port;

		protected:
			USBPort getPort() const { return port; }
			virtual void onStart();
			virtual void onStop();
			virtual void onProcess();

		public:
			UsbDevice(USBPort port);

			void start();
			void stop();
			void process();
	};
}


#endif // __STM32_eosUSBDevice__
