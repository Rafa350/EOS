#ifndef __STM32_eosUSB__
#define __STM32_eosUSB__


// EOS includes
//
#include "eos.h"
#include "HAL/halUSB.h"


namespace eos {

#ifndef USB_NVIC_PRIORITY
	#define USB_NVIC_PRIORITY  1
#endif

	class UsbBase {
		private:
			USBPort port;

		protected:
			virtual void onInitialize();

        public:
            UsbBase(USBPort port);
            virtual ~UsbBase() {}

            USBPort getPort() const { return port; }

            void initialize();
    };

}


#endif // __STM32_eosUSB__
