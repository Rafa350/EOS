#ifndef __STM32_eosUSBHost__
#define __STM32_eosUSBHost__


// EOS includes
//
#include "eos.h"
#include "Controllers/Usb/eosUSB.h"
#include "HAL/halUSB.h"


namespace eos {
    
    typedef struct {
        USBPort port;
    } USBHostInitializeInfo;
    
    
    class UsbHost: public UsbBase {
        public:
            void initialize(const USBHostInitializeInfo *info);
            void start();
            void stop();
            void process();
    };
}


#endif // __STM32_halUSBHost__
