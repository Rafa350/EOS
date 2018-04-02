#ifndef __STM32_halGPIO__
#define	__STM32_halGPIO__


// EOS includes
//
#include "eos.h"

// Standard includes
//
#include <stdint.h>

// STM32 includes
//
#if defined(EOS_STM32F4)
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio_ex.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_gpio_ex.h"
#else
#error Hardware no soportado
#endif


#ifdef	__cplusplus
extern "C" {
#endif


typedef struct {
	uint8_t port;
	uint8_t pin;
	uint32_t options;
	uint8_t alt;
} GPIOInitializePinInfo;

typedef struct {
	uint8_t port;
	uint16_t mask;
	uint32_t options;
	uint8_t alt;
} GPIOInitializePortInfo;

extern GPIO_TypeDef * const gpioTbl[];

// Identificado del port
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

// Identificador del pin
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

// Mascara de posicio del pin
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

// Funcio alternativa
// Sende funcio
#define HAL_GPIO_AF_NONE     0

// Funcio alternativa
// Funcio AF4
#define HAL_GPIO_AF4_I2C1    GPIO_AF4_I2C1
#define HAL_GPIO_AF4_I2C2    GPIO_AF4_I2C2
#define HAL_GPIO_AF4_I2C3    GPIO_AF4_I2C3
#define HAL_GPIO_AF4_I2C4    GPIO_AF4_I2C4

// Funcio alternativa
// Funcio AF5
#define HAL_GPIO_AF5_SPI1    GPIO_AF5_SPI1
#define HAL_GPIO_AF5_SPI2    GPIO_AF5_SPI2
#define HAL_GPIO_AF5_SPI3    GPIO_AF5_SPI3
#define HAL_GPIO_AF5_SPI4    GPIO_AF5_SPI4
#define HAL_GPIO_AF5_SPI5    GPIO_AF5_SPI5
#define HAL_GPIO_AF5_SPI6    GPIO_AF5_SPI6

// Funcio alternativa
// Funcio AF9
#define HAL_GPIO_AF9_LTDC    GPIO_AF9_LTDC

// Funcio alternativa
// Funcio AF12
#define HAL_GPIO_AF12_FMC    GPIO_AF12_FMC

// Funcio alternativa
// Funcio AF14
#define HAL_GPIO_AF14_LTDC   GPIO_AF14_LTDC

// Tipus de port
#define HAL_GPIO_MODE_OFFSET      0
#define HAL_GPIO_MODE_MASK        (0b1111 << HAL_GPIO_MODE_OFFSET)

#define HAL_GPIO_MODE_INPUT       (0 << HAL_GPIO_MODE_OFFSET)   // -Entrada digital
#define HAL_GPIO_MODE_OUTPUT_PP   (1 << HAL_GPIO_MODE_OFFSET)   // -Sortida push-pull
#define HAL_GPIO_MODE_OUTPUT_OD   (2 << HAL_GPIO_MODE_OFFSET)   // -Sortida open-drain
#define HAL_GPIO_MODE_ALT_PP      (3 << HAL_GPIO_MODE_OFFSET)   // -Sortida alternativa push-pull
#define HAL_GPIO_MODE_ALT_OD      (4 << HAL_GPIO_MODE_OFFSET)   // -Sortida alternativa open-drain
#define HAL_GPIO_MODE_ANALOG      (5 << HAL_GPIO_MODE_OFFSET)   // -Entrada/Sortida Analgica
#define HAL_GPIO_MODE_IT_POS      (6 << HAL_GPIO_MODE_OFFSET)   // -Interrupcio canvi a positiu
#define HAL_GPIO_MODE_IT_NEG	  (7 << HAL_GPIO_MODE_OFFSET)   // -Interrupcio canvi a negatiu
#define HAL_GPIO_MODE_IT_CHG      (8 << HAL_GPIO_MODE_OFFSET)   // -Interrupcio canvi

// Velocitat de conmutacio
#define HAL_GPIO_SPEED_OFFSET     4
#define HAL_GPIO_SPEED_MASK       (0b11 << HAL_GPIO_SPEED_OFFSET)

#define HAL_GPIO_SPEED_LOW        (0 << HAL_GPIO_SPEED_OFFSET)
#define HAL_GPIO_SPEED_MEDIUM	  (1 << HAL_GPIO_SPEED_OFFSET)
#define HAL_GPIO_SPEED_HIGH       (2 << HAL_GPIO_SPEED_OFFSET)
#define HAL_GPIO_SPEED_FAST       (3 << HAL_GPIO_SPEED_OFFSET)

// Resistencies pull-up
#define HAL_GPIO_PULL_OFFSET      6
#define HAL_GPIO_PULL_MASK        (0b11 << HAL_GPIO_PULL_OFFSET)

#define HAL_GPIO_PULL_NONE        (0 << HAL_GPIO_PULL_OFFSET)
#define HAL_GPIO_PULL_UP          (1 << HAL_GPIO_PULL_OFFSET)
#define HAL_GPIO_PULL_DOWN        (2 << HAL_GPIO_PULL_OFFSET)

// Valor inicial de la sortida
#define HAL_GPIO_INIT_OFFSET      8
#define HAL_GPIO_INIT_MASK        (0b1 << HAL_GPIO_INIT_OFFSET)

#define HAL_GPIO_INIT_CLR         (0 << HAL_GPIO_INIT_OFFSET)
#define HAL_GPIO_INIT_SET         (1 << HAL_GPIO_INIT_OFFSET)


#define halGPIOInitializePinInput(port, pin) \
	halGPIOInitialize(port, pin, HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);

#define halGPIOInitializePinOutput(port, pin) \
	halGPIOInitialize(port, pin, HAL_GPIO_MODE_OUTPUT_PP, HAL_GPIO_AF_NONE);


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

void halGPIOInitialize(uint8_t port, uint8_t pin, uint32_t options, uint8_t alt);


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halGPIO__

