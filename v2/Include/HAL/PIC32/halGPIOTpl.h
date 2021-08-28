#ifndef __PIC32_halGPIOTpl__
#define __PIC32_halGPIOTpl__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"


namespace eos {

    enum class GPIOPort: halGPIOPort {
        portA = HAL_GPIO_PORT_A,
        portB = HAL_GPIO_PORT_B,
        portC = HAL_GPIO_PORT_C,
        portD = HAL_GPIO_PORT_D,
        portE = HAL_GPIO_PORT_E,
        portF = HAL_GPIO_PORT_F,
        portG = HAL_GPIO_PORT_G
    };

    enum class GPIOPin: halGPIOPin {
        pin0 = HAL_GPIO_PIN_0,
        pin1 = HAL_GPIO_PIN_1,
        pin2 = HAL_GPIO_PIN_2,
        pin3 = HAL_GPIO_PIN_3,
        pin4 = HAL_GPIO_PIN_4,
        pin5 = HAL_GPIO_PIN_5,
        pin6 = HAL_GPIO_PIN_6,
        pin7 = HAL_GPIO_PIN_7,
        pin8 = HAL_GPIO_PIN_8,
        pin9 = HAL_GPIO_PIN_9,
        pin10 = HAL_GPIO_PIN_10,
        pin11 = HAL_GPIO_PIN_11,
        pin12 = HAL_GPIO_PIN_12,
        pin13 = HAL_GPIO_PIN_13,
        pin14 = HAL_GPIO_PIN_14,
        pin15 = HAL_GPIO_PIN_15
    };

    enum class GPIOSpeed: halGPIOOptions {
        low = HAL_GPIO_SPEED_LOW,
        medium = HAL_GPIO_SPEED_MEDIUM,
        high = HAL_GPIO_SPEED_HIGH,
        fast = HAL_GPIO_SPEED_FAST
    };

    enum class GPIODriver {
        pushPull,
        openDrain
    };

    enum class GPIOState: halGPIOOptions {
        set = HAL_GPIO_INIT_SET,
        clr = HAL_GPIO_INIT_CLR,
        noChange = HAL_GPIO_INIT_NOCHANGE
    };


    template <GPIOPort port, GPIOPin pin>
    class GPIOPinAdapter {
        public:
            inline static void initOutput(GPIOSpeed speed, GPIODriver driver, GPIOState state) {
                halGPIOOptions options =
                    HAL_GPIO_MODE_OUTPUT_PP |
                    halGPIOOptions(speed) |
                    halGPIOOptions(driver) |
                    halGPIOOptions(state);
                halGPIOInitializePin(halGPIOPort(port), halGPIOPin(pin), options, HAL_GPIO_AF_NONE);
            }

            inline static void initialize(halGPIOOptions options) {
                halGPIOInitializePin(halGPIOPort(port), halGPIOPin(pin), options, HAL_GPIO_AF_NONE);
            }

            inline static void set() {
                halGPIOSetPin(halGPIOPort(port), halGPIOPin(pin));
            }

            inline static void clear() {
                halGPIOClearPin(halGPIOPort(port), halGPIOPin(pin));
            }

            inline static void toggle() {
                halGPIOTogglePin(halGPIOPort(port), halGPIOPin(pin));
            }

            inline static void write(bool value) {
                if (value)
                    halGPIOSetPin(halGPIOPort(port), halGPIOPin(pin));
                else
                    halGPIOClearPin(halGPIOPort(port), halGPIOPin(pin));
            }

			inline static GPIOPort getPort() {
				return port;
			}

			inline static GPIOPin getPin() {
				return pin;
			}

			inline GPIOPinAdapter& operator = (bool b) {
				halGPIOWritePin(halGPIOPort(port), halGPIOPin(pin), b);
				return *this;
			}
    };

    
#ifdef HAL_GPIO_PORT_A
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin0> PIN_A0;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin1> PIN_A1;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin2> PIN_A2;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin3> PIN_A3;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin4> PIN_A4;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin5> PIN_A5;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin6> PIN_A6;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin7> PIN_A7;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin8> PIN_A8;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin9> PIN_A9;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin10> PIN_A10;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin11> PIN_A11;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin12> PIN_A12;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin13> PIN_A13;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin14> PIN_A14;
	typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin15> PIN_A15;
#endif

#ifdef HAL_GPIO_PORT_B
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin0> PIN_B0;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin1> PIN_B1;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin2> PIN_B2;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin3> PIN_B3;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin4> PIN_B4;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin5> PIN_B5;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin6> PIN_B6;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin7> PIN_B7;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin8> PIN_B8;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin9> PIN_B9;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin10> PIN_B10;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin11> PIN_B11;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin12> PIN_B12;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin13> PIN_B13;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin14> PIN_B14;
	typedef GPIOPinAdapter<GPIOPort::portB, GPIOPin::pin15> PIN_B15;
#endif

#ifdef HAL_GPIO_PORT_C
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin0> PIN_C0;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin1> PIN_C1;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin2> PIN_C2;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin3> PIN_C3;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin4> PIN_C4;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin5> PIN_C5;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin6> PIN_C6;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin7> PIN_C7;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin8> PIN_C8;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin9> PIN_C9;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin10> PIN_C10;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin11> PIN_C11;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin12> PIN_C12;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin13> PIN_C13;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin14> PIN_C14;
	typedef GPIOPinAdapter<GPIOPort::portC, GPIOPin::pin15> PIN_C15;
#endif

#ifdef HAL_GPIO_PORT_D
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin0> PIN_D0;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin1> PIN_D1;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin2> PIN_D2;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin3> PIN_D3;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin4> PIN_D4;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin5> PIN_D5;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin6> PIN_D6;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin7> PIN_D7;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin8> PIN_D8;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin9> PIN_D9;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin10> PIN_D10;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin11> PIN_D11;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin12> PIN_D12;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin13> PIN_D13;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin14> PIN_D14;
	typedef GPIOPinAdapter<GPIOPort::portD, GPIOPin::pin15> PIN_D15;
#endif

#ifdef HAL_GPIO_PORT_E
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin0> PIN_E0;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin1> PIN_E1;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin2> PIN_E2;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin3> PIN_E3;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin4> PIN_E4;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin5> PIN_E5;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin6> PIN_E6;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin7> PIN_E7;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin8> PIN_E8;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin9> PIN_E9;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin10> PIN_E10;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin11> PIN_E11;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin12> PIN_E12;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin13> PIN_E13;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin14> PIN_E14;
	typedef GPIOPinAdapter<GPIOPort::portE, GPIOPin::pin15> PIN_E15;
#endif

#ifdef HAL_GPIO_PORT_F
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin0> PIN_F0;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin1> PIN_F1;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin2> PIN_F2;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin3> PIN_F3;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin4> PIN_F4;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin5> PIN_F5;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin6> PIN_F6;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin7> PIN_F7;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin8> PIN_F8;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin9> PIN_F9;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin10> PIN_F10;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin11> PIN_F11;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin12> PIN_F12;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin13> PIN_F13;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin14> PIN_F14;
	typedef GPIOPinAdapter<GPIOPort::portF, GPIOPin::pin15> PIN_F15;
#endif

#ifdef HAL_GPIO_PORT_G
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin0> PIN_G0;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin1> PIN_G1;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin2> PIN_G2;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin3> PIN_G3;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin4> PIN_G4;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin5> PIN_G5;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin6> PIN_G6;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin7> PIN_G7;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin8> PIN_G8;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin9> PIN_G9;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin10> PIN_G10;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin11> PIN_G11;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin12> PIN_G12;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin13> PIN_G13;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin14> PIN_G14;
	typedef GPIOPinAdapter<GPIOPort::portG, GPIOPin::pin15> PIN_G15;
#endif

}


#endif // __PIC32_halGPIOTpl__
