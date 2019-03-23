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
        protected:
            void initializePort(USBPort port);
    };

}


#endif // __STM32_eosUSB__
