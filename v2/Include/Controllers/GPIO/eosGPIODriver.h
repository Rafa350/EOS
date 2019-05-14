#ifndef __eosGPIODriver__
#define __eosGPIODriver__


// EOS includes
//
#include "eos.h"
#include "hal/halGPIO.h"


namespace eos {

	template <GPIOPort port, GPIOPin pin>
    class GPIOPinDriver {
    	public:
    		inline static void initialize(GPIOOptions options) {
    			halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);
    		}

    		inline static void set() {
    			halGPIOSetPin(port, pin);
    		}

    		inline static void clear() {
    			halGPIOClearPin(port, pin);
    		}

    		inline static void toggle() {
    			halGPIOTogglePin(port, pin);
    		}

    		inline static bool read() {
    			return halGPIOReadPin(port, pin);
    		}
    };

	template <GPIOPort port, GPIOMask mask>
	class GPIOPortDriver {
		public:
			inline static void initialize(GPIOOptions options) {
				halGPIOInitializePort(port, mask, options, HAL_GPIO_AF_NONE);
			}

			inline static uint32_t read() {
    			return halGPIOReadPort(port);
    		}

			inline static void write(uint32_t data) {
    			halGPIOWritePort(port, data);
    		}
	};
}



#endif // __eosGPIODriver__
