#ifndef __STM32_halGPIOTpl__
#define __STM32_halGPIOTpl__


// EOS includes
//
#include "HAL/hal.h"
#include "HAL/STM32/halGPIO.h"


namespace eos {

	template <GPIOPort port, GPIOPin pin>
	class GPIOPinAdapter {
		public:
			inline static void initialize(GPIOOptions options) {
				halGPIOInitializePin(port, pin, options, HAL_GPIO_AF_NONE);
			}
			inline static void initialize(GPIOOptions options, GPIOAlt alt) {
				halGPIOInitializePin(port, pin, options, alt);
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

			inline static GPIOPort getPort() {
				return port;
			}

			inline static GPIOPin getPin() {
				return port;
			}
	};

    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_0> PA0;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_1> PA1;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_2> PA2;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_3> PA3;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_4> PA4;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_5> PA5;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_6> PA6;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_7> PA7;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_8> PA8;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_9> PA9;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_10> PA10;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_11> PA11;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_12> PA12;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_13> PA13;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_14> PA14;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_A, HAL_GPIO_PIN_15> PA15;

    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_0> PB0;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_1> PB1;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_2> PB2;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_3> PB3;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_4> PB4;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_5> PB5;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_6> PB6;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_7> PB7;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_8> PB8;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_9> PB9;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_10> PB10;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_11> PB11;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_12> PB12;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_13> PB13;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_14> PB14;
    typedef GPIOPinAdapter<HAL_GPIO_PORT_B, HAL_GPIO_PIN_15> PB15;

}


#endif // __STM32_halGPIOTpl__
