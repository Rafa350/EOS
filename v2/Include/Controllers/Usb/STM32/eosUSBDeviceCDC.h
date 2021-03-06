#ifndef __STM32_eosUSBDeviceCDC__
#define __STM32_eosUSBDeviceCDC__


// EOS includes
//
#include "eos.h"
#include "Controllers/Usb/eosUSBDevice.h"


namespace eos {

	class UsbDeviceCDC: public UsbDevice {
		protected:
			void onInitialize();
			void onProcess();

		public:
			UsbDeviceCDC(USBPort port);
			virtual ~UsbDeviceCDC() {}
	};

}


#endif // __STM32_eosUSBDeviceCDC__
