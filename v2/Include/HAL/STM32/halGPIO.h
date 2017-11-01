#ifndef __STM32_halGPIO__
#define	__STM32_halGPIO__


// Standard includes
//
#include <stdint.h>


// STM32 includes
//
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_gpio_ex.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t GPIOPort;
typedef uint8_t GPIOPin;
typedef uint8_t GPIOOptions;
typedef uint8_t GPIOFunction;

typedef struct {
	GPIOPort port;
	GPIOPin pin;
	GPIOOptions options;
	GPIOFunction function;
} GPIOInitializePinInfo;

typedef struct {
	GPIOPort port;
	uint16_t mask;
	GPIOOptions options;
	GPIOFunction function;
} GPIOInitializePortInfo;

extern GPIO_TypeDef * const gpioTbl[];


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
#define HAL_GPIO_PORT_K      10

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
#define HAL_GPIO_PIN_10      10
#define HAL_GPIO_PIN_11      11
#define HAL_GPIO_PIN_12      12
#define HAL_GPIO_PIN_13      13
#define HAL_GPIO_PIN_14      14
#define HAL_GPIO_PIN_15      15

#define HAL_GPIO_POS_0       ((uint32_t) 1 << HAL_GPIO_PIN_0)
#define HAL_GPIO_POS_1       ((uint32_t) 1 << HAL_GPIO_PIN_1)
#define HAL_GPIO_POS_2       ((uint32_t) 1 << HAL_GPIO_PIN_2)
#define HAL_GPIO_POS_3       ((uint32_t) 1 << HAL_GPIO_PIN_3)
#define HAL_GPIO_POS_4       ((uint32_t) 1 << HAL_GPIO_PIN_4)
#define HAL_GPIO_POS_5       ((uint32_t) 1 << HAL_GPIO_PIN_5)
#define HAL_GPIO_POS_6       ((uint32_t) 1 << HAL_GPIO_PIN_6)
#define HAL_GPIO_POS_7       ((uint32_t) 1 << HAL_GPIO_PIN_7)
#define HAL_GPIO_POS_8       ((uint32_t) 1 << HAL_GPIO_PIN_8)
#define HAL_GPIO_POS_9       ((uint32_t) 1 << HAL_GPIO_PIN_9)
#define HAL_GPIO_POS_10      ((uint32_t) 1 << HAL_GPIO_PIN_10)
#define HAL_GPIO_POS_11      ((uint32_t) 1 << HAL_GPIO_PIN_11)
#define HAL_GPIO_POS_12      ((uint32_t) 1 << HAL_GPIO_PIN_12)
#define HAL_GPIO_POS_13      ((uint32_t) 1 << HAL_GPIO_PIN_13)
#define HAL_GPIO_POS_14      ((uint32_t) 1 << HAL_GPIO_PIN_14)
#define HAL_GPIO_POS_15      ((uint32_t) 1 << HAL_GPIO_PIN_15)

#define HAL_GPIO_AF_NONE     0
#define HAL_GPIO_AF12_FMC    GPIO_AF12_FMC
#define HAL_GPIO_AF9_LTDC    GPIO_AF9_LTDC
#define HAL_GPIO_AF14_LTDC   GPIO_AF14_LTDC
#define HAL_GPIO_AF5_SPI1    GPIO_AF5_SPI1
#define HAL_GPIO_AF5_SPI2    GPIO_AF5_SPI2
#define HAL_GPIO_AF5_SPI3    GPIO_AF5_SPI3
#define HAL_GPIO_AF5_SPI4    GPIO_AF5_SPI4
#define HAL_GPIO_AF5_SPI5    GPIO_AF5_SPI5
#define HAL_GPIO_AF5_SPI6    GPIO_AF5_SPI6

#define HAL_GPIO_MODE_MASK             0b00000011
#define HAL_GPIO_MODE_INPUT            0b00000000
#define HAL_GPIO_MODE_OUTPUT           0b00000001
#define HAL_GPIO_MODE_FUNCTION         0b00000010
#define HAL_GPIO_MODE_ANALOG           0b00000011

#define HAL_GPIO_SPEED_MASK            0b00001100
#define HAL_GPIO_SPEED_LOW             0b00000000
#define HAL_GPIO_SPEED_MEDIUM	       0b00000100
#define HAL_GPIO_SPEED_HIGH            0b00001000
#define HAL_GPIO_SPEED_FAST            0b00001100

#define HAL_GPIO_OPENDRAIN_MASK        0b00100000
#define HAL_GPIO_OPENDRAIN_DISABLED    0b00000000
#define HAL_GPIO_OPENDRAIN_ENABLED     0b00100000

#define HAL_GPIO_PULL_MASK             0b11000000
#define HAL_GPIO_PULL_NONE             0b00000000
#define HAL_GPIO_PULL_UP               0b01000000
#define HAL_GPIO_PULL_DOWN             0b10000000

#define HAL_GPIO_INIT_MASK
#define HAL_GPIO_INIT_CLR
#define HAL_GPIO_INIT_SET


#define halGPIOInitializePinInput(port, pin) \
	halGPIOInitialize(port, pin, HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);

#define halGPIOInitializePinOutput(port, pin) \
	halGPIOInitialize(port, pin, HAL_GPIO_MODE_OUTPUT, HAL_GPIO_AF_NONE);


#define halGPIOSetPin(port, pin) \
	gpioTbl[port]->BSRR = ((uint32_t) 1) << (pin)

#define halGPIOClearPin(port, pin) \
	gpioTbl[port]->BSRR = ((uint32_t) 1) << (pin + 16)

#define halGPIOTogglePin(port, pin) \
	gpioTbl[port]->ODR ^= ((uint32_t) 1) << (pin)

#define halGPIOReadPin(port, pin) \
	(gpioTbl[port]->IDR & (((uint32_t) 1) << pin)) != 0;


#define halGPIOWritePort(port, data) \
    gpioTbl[port]->ODR = data

#define halGPIOReadPort(port) \
    gpioTbl[port]->IDR


void halGPIOInitializePins(const GPIOInitializePinInfo *info, uint8_t count);
void halGPIOInitializePin(const GPIOInitializePinInfo *info);

void halGPIOInitializePorts(const GPIOInitializePortInfo *info, uint8_t count);
void halGPIOInitializePort(const GPIOInitializePortInfo *info);

void halGPIOInitialize(GPIOPort port, GPIOPin pin, GPIOOptions options, GPIOFunction function);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halGPIO__

