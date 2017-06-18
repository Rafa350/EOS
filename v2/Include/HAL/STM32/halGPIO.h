#ifndef __EOS_HAL_STM32_GPIO_H
#define	__EOS_HAL_STM32_GPIO_H


#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t GPIOPort;
typedef uint8_t GPIOPin;
typedef uint8_t GPIOOptions;

typedef struct {
	GPIOPort port;
	GPIOPin pin;
	GPIOOptions options;
} GPIOInitializeInfo;

extern GPIO_TypeDef *gpioPortRegs[];


#define HAL_GPIO_PORT_A      0
#define HAL_GPIO_PORT_B      1
#define HAL_GPIO_PORT_C      2
#define HAL_GPIO_PORT_D      3
#define HAL_GPIO_PORT_E      4
#define HAL_GPIO_PORT_F      5
#define HAL_GPIO_PORT_G      6
#define HAL_GPIO_PORT_H      7
#define HAL_GPIO_PORT_I      8
#define HAL_GPIO_PORT_J      9
#define HAL_GPIO_PORT_K     10

#define HAL_GPIO_PIN_0       0
#define HAL_GPIO_PIN_1       1
#define HAL_GPIO_PIN_2       2
#define HAL_GPIO_PIN_3       3
#define HAL_GPIO_PIN_4       4
#define HAL_GPIO_PIN_5       5
#define HAL_GPIO_PIN_6       6
#define HAL_GPIO_PIN_7       7
#define HAL_GPIO_PIN_8       8
#define HAL_GPIO_PIN_9       9
#define HAL_GPIO_PIN_10     10
#define HAL_GPIO_PIN_11     11
#define HAL_GPIO_PIN_12     12
#define HAL_GPIO_PIN_13     13
#define HAL_GPIO_PIN_14     14
#define HAL_GPIO_PIN_15     15

#define HAL_GPIO_AF_LTDC    GPIO_AF_LTDC

#define HAL_GPIO_MODE_MASK             0b00000011
#define HAL_GPIO_MODE_INPUT            0b00000000
#define HAL_GPIO_MODE_OUTPUT           0b00000001
#define HAL_GPIO_MODE_AF               0b00000010
#define HAL_GPIO_MODE_ANALOG           0b00000011

#define HAL_GPIO_SPEED_MASK            0b00001100
#define HAL_GPIO_SPEED_LOW             0b00000000
#define HAL_GPIO_SPEED_MEDIUM	       0b00000100
#define HAL_GPIO_SPEED_FAST            0b00001000
#define HAL_GPIO_SPEED_HIGH            0b00001100

#define HAL_GPIO_OPENDRAIN_MASK        0b00100000
#define HAL_GPIO_OPENDRAIN_DISABLED    0b00000000
#define HAL_GPIO_OPENDRAIN_ENABLED     0b00100000

#define HAL_GPIO_PULLUPDN_MASK         0b11000000
#define HAL_GPIO_PULLUPDN_NONE         0b00000000
#define HAL_GPIO_PULLUPDN_UP           0b01000000
#define HAL_GPIO_PULLUPDN_DOWN         0b10000000

#define halGPIOInitializePinInput(port, pin) \
	RCC->AHB1ENR |= 1 << port; \
	gpioPortRegs[port]->MODER &= ~(((uint32_t) 0b11) << (pin * 2))

#define halGPIOInitializePinOutput(port, pin) \
	RCC->AHB1ENR |= 1 << port; \
	gpioPortRegs[port]->MODER &= ~(((uint32_t) 0b11) << (pin * 2)); \
	gpioPortRegs[port]->MODER |= ((uint32_t) 0b01) << (pin * 2)

#define halGPIOInitializeAlternatePin(port, pin, alternate) \
	gpioPortRegs[port]->AFR[pin >> 3] &= ~(0x0F << ((pin & 0x07) * 4)); \
	gpioPortRegs[port]->AFR[pin >> 3] |= (alternate << ((pin & 0x07) * 4));

#define halGPIOSetPin(port, pin) \
	gpioPortRegs[port]->BSRRL = ((uint16_t) 1) << (pin)

#define halGPIOClearPin(port, pin) \
	gpioPortRegs[port]->BSRRH = ((uint16_t) 1) << (pin)

#define halGPIOTogglePin(port, pin) \
	gpioPortRegs[port]->ODR ^= ((uint32_t) 1) << (pin)

#define halGPIOReadPin(port, pin) \
	(gpioPortRegs[port]->IDR & (((uint32_t) 1) << pin)) != 0;


#define halGPIOWritePort(port, data) \
    gpioPortRegs[port]->ODR = data

#define halGPIOReadPort(port) \
    gpioPortRegs[port]->IDR


void halGPIOInitialize(GPIOInitializeInfo *info, uint8_t count);

void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIOOptions options);
void halGPIOInitializePort(GPIOPort port, GPIOOptions options, uint16_t mask);

void halGPIOInitializePortInput(GPIOPort port, uint16_t mask);
void halGPIOInitializePortOutput(GPIOPort port, uint16_t mask);

#ifdef	__cplusplus
}
#endif


#endif

