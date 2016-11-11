#ifndef __EOS_HAL_GPIO_STM32F_H
#define	__EOS_HAL_GPIO_STM32F_H


#include "stm32f4xx.h"

#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t GPIOPort;
typedef uint8_t GPIOPin;
typedef uint8_t GPIOOptions;

extern GPIO_TypeDef *gpioPortRegs[];


#define GPIO_PORT_A     0
#define GPIO_PORT_B     1
#define GPIO_PORT_C     2
#define GPIO_PORT_D     3
#define GPIO_PORT_E     4
#define GPIO_PORT_F     5
#define GPIO_PORT_G     6
#define GPIO_PORT_H     7
#define GPIO_PORT_I     8
#define GPIO_PORT_J     9
#define GPIO_PORT_K     10

#define GPIO_PIN_0      0
#define GPIO_PIN_1      1
#define GPIO_PIN_2      2
#define GPIO_PIN_3      3
#define GPIO_PIN_4      4
#define GPIO_PIN_5      5
#define GPIO_PIN_6      6
#define GPIO_PIN_7      7
#define GPIO_PIN_8      8
#define GPIO_PIN_9      9
#define GPIO_PIN_10     10
#define GPIO_PIN_11     11
#define GPIO_PIN_12     12
#define GPIO_PIN_13     13
#define GPIO_PIN_14     14
#define GPIO_PIN_15     15

#define GPIO_DIRECTION_MASK       0b00000001
#define GPIO_DIRECTION_INPUT      0b00000000
#define GPIO_DIRECTION_OUTPUT     0b00000001

#define GPIO_OPENDRAIN_MASK       0b00000010
#define GPIO_OPENDRAIN_DISABLED   0b00000000
#define GPIO_OPENDRAIN_ENABLED    0b00000010

#define GPIO_PULLUPDN_MASK        0b11000000
#define GPIO_PULLUPDN_NONE        0b00000000
#define GPIO_PULLUPDN_UP          0b01000000
#define GPIO_PULLUPDN_DOWN        0b10000000

#define halGPIOInitializePinInput(port, pin) \
	gpioPortRegs[port]->MODER &= ~(0b11 << (pin * 2))

#define halGPIOInitializePinOutput(port, pin) \
	gpioPortRegs[port]->MODER &= ~(0b11 << (pin * 2)); \
	gpioPortRegs[port]->MODER |= 0b01 << (pin * 2)

#define halGPIOSetPin(port, pin) \
	gpioPortRegs[port]->BSRR = 1 << (pin)

#define halGPIOClearPin(port, pin) \
	gpioPortRegs[port]->BSRR = 1 << ((pin) + 16)

#define halGPIOTogglePin(port, pin) \
	gpioPortRegs[port]->ODR ^= 1 << (pin)

#define halGPIOReadPin(port, pin) \
	gpioPortRegs[port]->IDR & (1 << pin) != 0;


#define halGPIOWritePort(port, data) \
    gpioPortRegs[port]->ODR = data

#define halGPIOReadPort(port) \
    gpioPortRegs[port]->IDR


void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIOOptions options);
void halGPIOInitializePort(GPIOPort port, GPIOOptions options, uint16_t mask);

void halGPIOInitializePortInput(GPIOPort port, uint16_t mask);
void halGPIOInitializePortOutput(GPIOPort port, uint16_t mask);


#ifdef	__cplusplus
}
#endif


#endif

