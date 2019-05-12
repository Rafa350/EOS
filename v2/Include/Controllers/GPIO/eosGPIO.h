#ifndef __eosGPIO__
#define __eosGPIO__


// EOS includes
//
#include "eos.h"
#include "hal/halGPIO.h"


namespace eos {

	template <GPIOPort port, GPIOPin pin>
    class GPIOOutputPin {
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

    		//void write(bool v);

    		inline static bool read() {
    			return halGPIOReadPin(port, pin);
    		}
    };
}



#endif // __eosGPIO__
