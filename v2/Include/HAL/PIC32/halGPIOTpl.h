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
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin0> Pin_A0;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin1> Pin_A1;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin2> Pin_A2;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin3> Pin_A3;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin4> Pin_A4;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin5> Pin_A5;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin6> Pin_A6;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin7> Pin_A7;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin8> Pin_A8;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin9> Pin_A9;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin10> Pin_A10;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin11> Pin_A11;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin12> Pin_A12;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin13> Pin_A13;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin14> Pin_A14;
    typedef GPIOPinAdapter<GPIOPort::portA, GPIOPin::pin15> Pin_A15;
#endif

#ifdef HAL_GPIO_PORT_B
#endif
}


#endif // __PIC32_halGPIOTpl__
