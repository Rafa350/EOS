#ifndef __PIC32_halGPIOTpl__
#define __PIC32_halGPIOTpl__


// EOS includes
//
#include "eos.h"
#include "HAL/halGPIO.h"


namespace eos {

    enum class GpioPort: GPIOPort {
        portA = HAL_GPIO_PORT_A,
        portB = HAL_GPIO_PORT_B,
        portC = HAL_GPIO_PORT_C,
        portD = HAL_GPIO_PORT_D,
        portE = HAL_GPIO_PORT_E,
        portF = HAL_GPIO_PORT_F,
        portG = HAL_GPIO_PORT_G
    };

    enum class GpioPin: GPIOPin {
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


    template <GpioPort port, GpioPin pin>
    class GpioPinAdapter {
        public:
            inline static void initialize(GPIOOptions options) {
                halGPIOInitializePin(GPIOPort(port), GPIOPin(pin), options, HAL_GPIO_AF_NONE);
            }

            inline static void set() {
                halGPIOSetPin(GPIOPort(port), GPIOPin(pin));
            }

            inline static void clear() {
                halGPIOClearPin(GPIOPort(port), GPIOPin(pin));
            }

            inline static void toggle() {
                halGPIOTogglePin(GPIOPort(port), GPIOPin(pin));
            }

            inline static void write(bool value) {
                if (value)
                    halGPIOSetPin(GPIOPort(port), GPIOPin(pin));
                else
                    halGPIOClearPin(GPIOPort(port), GPIOPin(pin));
            }
    };


#ifdef HAL_GPIO_PORT_A
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin0> PA0;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin1> PA1;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin2> PA2;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin3> PA3;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin4> PA4;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin5> PA5;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin6> PA6;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin7> PA7;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin8> PA8;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin9> PA9;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin10> PA10;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin11> PA11;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin12> PA12;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin13> PA13;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin14> PA14;
    typedef GpioPinAdapter<GpioPort::portA, GpioPin::pin15> PA15;
#endif

#ifdef HAL_GPIO_PORT_B
#endif
}


#endif // __PIC32_halGPIOTpl__
