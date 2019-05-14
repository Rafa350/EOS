#ifndef __STM32_halGPIOTpl__
#define __STM32_halGPIOTpl__


// EOS includes
//
#include "eos.h"
#include "hal/halGPIO.h"


namespace eos {

	template <GPIO_TypeDef gpio>
    class GPIOPortAdapter {
    	public:
    		inline static void initialize(GPIOOptions options) {
    		}

    		inline static void set(uint32_t mask) {
    			(uint32_t*)(lat + 4) = mask;
    		}

    		inline static void clear(uint32_t mask) {
                (uint32_t*)(lat + 0) = mask;
    		}

    		inline static void toggle(uint32_t mask) {
    			(uint32_t*)(lat + 8) = mask;
    		}
            
            inline static void write(uint32_t value) {
                (uint32_t*)(port) = value;
            }

    		inline static uint32_t read() {
    			return (uint32_t*)(port);
    		}
    };
    
    typedef GPIOPortAdapter<GPIOA> PortA;
    typedef GPIOPortAdapter<GPIOB> PortB;
    typedef GPIOPortAdapter<GPIOC> PortC;
    typedef GPIOPortAdapter<GPIOD> PortD;
    typedef GPIOPortAdapter<GPIOE> PortE;

}


#endif // __STM32_halGPIOTpl__
