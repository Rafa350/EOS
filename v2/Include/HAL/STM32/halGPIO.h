#ifndef __STM32_halGPIO__
#define	__STM32_halGPIO__


// EOS includes
//
#include "eos.h"

// STM32 includes
//
#if defined(EOS_STM32F4)
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio_ex.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx.h"
#include "stm32f7xx_hal_gpio_ex.h"
#else
#error Hardware no soportado
#endif

// Standard includes
//
#include "stdint.h"


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint8_t GPIOPort;
typedef uint8_t GPIOPin;
typedef uint16_t GPIOMask;
typedef uint32_t GPIOOptions;
typedef uint8_t GPIOAlt;

typedef struct {
	GPIOPort port;
	GPIOPin pin;
	GPIOOptions options;
	GPIOAlt alt;
} GPIOInitializePinInfo;

typedef struct {
	GPIOPort port;
	GPIOMask mask;
	GPIOOptions options;
	GPIOAlt alt;
} GPIOInitializePortInfo;


extern GPIO_TypeDef * const gpioTbl[];


// Identificado del port
#define HAL_GPIO_PORT_A      ((GPIOPort) 0)
#define HAL_GPIO_PORT_B      ((GPIOPort) 1)
#define HAL_GPIO_PORT_C      ((GPIOPort) 2)
#define HAL_GPIO_PORT_D      ((GPIOPort) 3)
#define HAL_GPIO_PORT_E      ((GPIOPort) 4)
#define HAL_GPIO_PORT_F      ((GPIOPort) 5)
#define HAL_GPIO_PORT_G      ((GPIOPort) 6)
#define HAL_GPIO_PORT_H      ((GPIOPort) 7)
#define HAL_GPIO_PORT_I      ((GPIOPort) 8)
#define HAL_GPIO_PORT_J      ((GPIOPort) 9)
#define HAL_GPIO_PORT_K      ((GPIOPort) 10)

// Identificador del pin
#define HAL_GPIO_PIN_0       ((GPIOPin) 0)
#define HAL_GPIO_PIN_1       ((GPIOPin) 1)
#define HAL_GPIO_PIN_2       ((GPIOPin) 2)
#define HAL_GPIO_PIN_3       ((GPIOPin) 3)
#define HAL_GPIO_PIN_4       ((GPIOPin) 4)
#define HAL_GPIO_PIN_5       ((GPIOPin) 5)
#define HAL_GPIO_PIN_6       ((GPIOPin) 6)
#define HAL_GPIO_PIN_7       ((GPIOPin) 7)
#define HAL_GPIO_PIN_8       ((GPIOPin) 8)
#define HAL_GPIO_PIN_9       ((GPIOPin) 9)
#define HAL_GPIO_PIN_10      ((GPIOPin) 10)
#define HAL_GPIO_PIN_11      ((GPIOPin) 11)
#define HAL_GPIO_PIN_12      ((GPIOPin) 12)
#define HAL_GPIO_PIN_13      ((GPIOPin) 13)
#define HAL_GPIO_PIN_14      ((GPIOPin) 14)
#define HAL_GPIO_PIN_15      ((GPIOPin) 15)
#define HAL_GPIO_PIN_NONE    ((GPIOPin) 255)

// Mascara de posicio del pin
#define HAL_GPIO_POS_0       ((GPIOMask) 1 << 0)
#define HAL_GPIO_POS_1       ((GPIOMask) 1 << 1)
#define HAL_GPIO_POS_2       ((GPIOMask) 1 << 2)
#define HAL_GPIO_POS_3       ((GPIOMask) 1 << 3)
#define HAL_GPIO_POS_4       ((GPIOMask) 1 << 4)
#define HAL_GPIO_POS_5       ((GPIOMask) 1 << 5)
#define HAL_GPIO_POS_6       ((GPIOMask) 1 << 6)
#define HAL_GPIO_POS_7       ((GPIOMask) 1 << 7)
#define HAL_GPIO_POS_8       ((GPIOMask) 1 << 8)
#define HAL_GPIO_POS_9       ((GPIOMask) 1 << 9)
#define HAL_GPIO_POS_10      ((GPIOMask) 1 << 10)
#define HAL_GPIO_POS_11      ((GPIOMask) 1 << 11)
#define HAL_GPIO_POS_12      ((GPIOMask) 1 << 12)
#define HAL_GPIO_POS_13      ((GPIOMask) 1 << 13)
#define HAL_GPIO_POS_14      ((GPIOMask) 1 << 14)
#define HAL_GPIO_POS_15      ((GPIOMask) 1 << 15)
#define HAL_GPIO_POS_LO      ((GPIOMask) 0x00FF)
#define HAL_GPIO_POS_HI      ((GPIOMask) 0xFF00)
#define HAL_GPIO_POS_ALL     ((GPIOMask) 0xFFFF)

// Funcio alternativa
// Sense funcio asignada
#define HAL_GPIO_AF_NONE          ((GPIOAlt) 0)

// Funcio alternativa
// Funcio I2Cx
#define HAL_GPIO_AF4_I2C1         GPIO_AF4_I2C1
#define HAL_GPIO_AF4_I2C2         GPIO_AF4_I2C2
#define HAL_GPIO_AF4_I2C3         GPIO_AF4_I2C3
#define HAL_GPIO_AF4_I2C4         GPIO_AF4_I2C4

// Funcio alternativa
// Funcio SPIx
#define HAL_GPIO_AF5_SPI1         GPIO_AF5_SPI1
#define HAL_GPIO_AF5_SPI2         GPIO_AF5_SPI2
#define HAL_GPIO_AF5_SPI3         GPIO_AF5_SPI3
#define HAL_GPIO_AF5_SPI4         GPIO_AF5_SPI4
#define HAL_GPIO_AF5_SPI5         GPIO_AF5_SPI5
#define HAL_GPIO_AF5_SPI6         GPIO_AF5_SPI6

// Funcio alternativa
// Funcio LTDC
#define HAL_GPIO_AF9_LTDC         GPIO_AF9_LTDC
#define HAL_GPIO_AF14_LTDC        GPIO_AF14_LTDC

// Funcio alternativa
// Funcio OGTx
#define HAL_GPIO_AF10_OGT1_FS     GPIO_AF10_OTG_FS
#define HAL_GPIO_AF10_OGT2_HS     GPIO_AF10_OGT_HS
#define HAL_GPIO_AF12_OGT2_FS     GPIO_AF12_OTG_HS_FS

// Funcio alternativa
// Funcio FMC
#define HAL_GPIO_AF12_FMC         GPIO_AF12_FMC

// Funcio alternativa
// Funcio SDMMC
#define HAL_GPIO_AF12_SDMMC1      GPIO_AF12_SDMMC1

// Funcio alternativa
// Funcio DCMI
#define HAL_GPIO_AF13_DCMI        GPIO_AF13_DCMI

// Tipus de port
#define HAL_GPIO_MODE_POS         0u
#define HAL_GPIO_MODE_BITS        0b1111u
#define HAL_GPIO_MODE_MASK        (HAL_GPIO_MODE_BITS << HAL_GPIO_MODE_POS)

#define HAL_GPIO_MODE_INPUT       (0u << HAL_GPIO_MODE_POS) // -Entrada digital
#define HAL_GPIO_MODE_OUTPUT_PP   (1u << HAL_GPIO_MODE_POS) // -Sortida push-pull
#define HAL_GPIO_MODE_OUTPUT_OD   (2u << HAL_GPIO_MODE_POS) // -Sortida open-drain
#define HAL_GPIO_MODE_ALT_PP      (3u << HAL_GPIO_MODE_POS) // -Sortida alternativa push-pull
#define HAL_GPIO_MODE_ALT_OD      (4u << HAL_GPIO_MODE_POS) // -Sortida alternativa open-drain
#define HAL_GPIO_MODE_ANALOG      (5u << HAL_GPIO_MODE_POS) // -Entrada/Sortida Analgica
#define HAL_GPIO_MODE_IT_POS      (6u << HAL_GPIO_MODE_POS) // -Interrupcio canvi a positiu
#define HAL_GPIO_MODE_IT_NEG	  (7u << HAL_GPIO_MODE_POS) // -Interrupcio canvi a negatiu
#define HAL_GPIO_MODE_IT_CHG      (8u << HAL_GPIO_MODE_POS) // -Interrupcio canvi

// Velocitat de conmutacio
#define HAL_GPIO_SPEED_POS        4u
#define HAL_GPIO_SPEED_BITS       0b11u
#define HAL_GPIO_SPEED_MASK       (HAL_GPIO_SPEED_BITS << HAL_GPIO_SPEED_POS)

#define HAL_GPIO_SPEED_LOW        (0u << HAL_GPIO_SPEED_POS)
#define HAL_GPIO_SPEED_MEDIUM	  (1u << HAL_GPIO_SPEED_POS)
#define HAL_GPIO_SPEED_HIGH       (2u << HAL_GPIO_SPEED_POS)
#define HAL_GPIO_SPEED_FAST       (3u << HAL_GPIO_SPEED_POS)

// Resistencies pull-up
#define HAL_GPIO_PULL_POS         6u
#define HAL_GPIO_PULL_BITS        0b11u
#define HAL_GPIO_PULL_MASK        (HAL_GPIO_PULL_BITS << HAL_GPIO_PULL_POS)

#define HAL_GPIO_PULL_NONE        (0u << HAL_GPIO_PULL_POS)
#define HAL_GPIO_PULL_UP          (1u << HAL_GPIO_PULL_POS)
#define HAL_GPIO_PULL_DOWN        (2u << HAL_GPIO_PULL_POS)

// Valor inicial de la sortida
#define HAL_GPIO_INIT_POS         8u
#define HAL_GPIO_INIT_BITS        0b1u
#define HAL_GPIO_INIT_MASK        (HAL_GPIO_INIT_BITS << HAL_GPIO_INIT_POS)

#define HAL_GPIO_INIT_CLR         (0u << HAL_GPIO_INIT_POS)
#define HAL_GPIO_INIT_SET         (1u << HAL_GPIO_INIT_POS)


#define halGPIOInitializePinInput(port, pin) \
	halGPIOInitializePin(port, pin, HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);

#define halGPIOInitializePinOutput(port, pin) \
	halGPIOInitializePin(port, pin, HAL_GPIO_MODE_OUTPUT_PP, HAL_GPIO_AF_NONE);

#if 1
#define halGPIOSetPin(port, pin) \
	gpioTbl[port]->BSRR = ((uint32_t) 1) << (pin)

#define halGPIOClearPin(port, pin) \
	gpioTbl[port]->BSRR = ((uint32_t) 1) << ((pin) + 16)

#define halGPIOTogglePin(port, pin) \
	gpioTbl[port]->ODR ^= ((uint32_t) 1) << (pin)
#endif

#define halGPIOReadPin(port, pin) \
	((gpioTbl[port]->IDR & (((uint32_t) 1) << (pin))) != 0)


#define halGPIOWritePort(port, data) \
    gpioTbl[port]->ODR = data

#define halGPIOReadPort(port) \
    gpioTbl[port]->IDR

void halGPIOInitializePins(const GPIOInitializePinInfo *pInfo, uint_fast8_t count);
void halGPIOInitializePorts(const GPIOInitializePortInfo *pInfo, uint_fast8_t count);
void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIOOptions options, GPIOAlt alt);

#if 0
void halGPIOClearPin(GPIOPort port, GPIOPin pin);
void halGPIOSetPin(GPIOPort port, GPIOPin pin);
void halGPIOTogglePin(GPIOPort port, GPIOPin pin);
#endif


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halGPIO__

