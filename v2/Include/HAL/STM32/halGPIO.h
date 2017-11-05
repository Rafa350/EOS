#ifndef __STM32_halGPIO__
#define	__STM32_halGPIO__


// Standard includes
//
#include <stdint.h>

// STM32 includes
//
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio_ex.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t GPIOFunction;

typedef struct {
	uint8_t port;
	uint8_t pin;
	uint32_t options;
	GPIOFunction function;
} GPIOInitializePinInfo;

typedef struct {
	uint8_t port;
	uint16_t mask;
	uint32_t options;
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

// Tipus de port
#define HAL_GPIO_MODE_MASK             0x00000003
#define HAL_GPIO_MODE_INPUT            0x00000000
#define HAL_GPIO_MODE_OUTPUT           0x00000001
#define HAL_GPIO_MODE_FUNCTION         0x00000002
#define HAL_GPIO_MODE_ANALOG           0x00000003

// Velocitat de conmutacio
#define HAL_GPIO_SPEED_MASK            0x0000000C
#define HAL_GPIO_SPEED_LOW             0x0000000C
#define HAL_GPIO_SPEED_MEDIUM	       0x0000000D
#define HAL_GPIO_SPEED_HIGH            0x0000000E
#define HAL_GPIO_SPEED_FAST            0x0000000F

// Sortida tipus Open-Drain
#define HAL_GPIO_OPENDRAIN_MASK        0x00000010
#define HAL_GPIO_OPENDRAIN_DISABLED    0x00000000
#define HAL_GPIO_OPENDRAIN_ENABLED     0x00000010

// Resistencies pull-up
#define HAL_GPIO_PULL_MASK             0x00000060
#define HAL_GPIO_PULL_NONE             0x00000020
#define HAL_GPIO_PULL_UP               0x00000040
#define HAL_GPIO_PULL_DOWN             0x00000060

// Valor inicial de la sortida
#define HAL_GPIO_INIT_MASK             0x00000080
#define HAL_GPIO_INIT_CLR              0x00000000
#define HAL_GPIO_INIT_SET              0x00000080


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

void halGPIOInitialize(uint8_t port, uint8_t pin, uint32_t options, GPIOFunction function);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halGPIO__

