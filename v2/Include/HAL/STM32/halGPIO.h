#ifndef __STM32_halGPIO__
#define	__STM32_halGPIO__


// EOS includes
//
#include "eos.h"

// STM32 includes
//
#if defined(EOS_STM32F4)
#include "stm32f4xx_hal_gpio_ex.h"
#elif defined(EOS_STM32F7)
#include "stm32f7xx_hal_gpio_ex.h"
#else
#error Hardware no soportado
#endif


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
#define HAL_GPIO_PORT_NONE   ((GPIOPort) 255)

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

// Funcio alternativa AF4
// -Funcio I2Cx
#define HAL_GPIO_AF4_I2C1         GPIO_AF4_I2C1
#define HAL_GPIO_AF4_I2C2         GPIO_AF4_I2C2
#define HAL_GPIO_AF4_I2C3         GPIO_AF4_I2C3
#define HAL_GPIO_AF4_I2C4         GPIO_AF4_I2C4

// Funcio alternativa AF5
// -Funcio SPIx
#define HAL_GPIO_AF5_SPI1         GPIO_AF5_SPI1
#define HAL_GPIO_AF5_SPI2         GPIO_AF5_SPI2
#define HAL_GPIO_AF5_SPI3         GPIO_AF5_SPI3
#define HAL_GPIO_AF5_SPI4         GPIO_AF5_SPI4
#define HAL_GPIO_AF5_SPI5         GPIO_AF5_SPI5
#define HAL_GPIO_AF5_SPI6         GPIO_AF5_SPI6

// Funcio alternativa AF9
// -Funcio LTDC
#define HAL_GPIO_AF9_LTDC         GPIO_AF9_LTDC

// Funcio alternativa AF10
// -Funcio OGTx
#define HAL_GPIO_AF10_OGT1_FS     GPIO_AF10_OTG_FS
#define HAL_GPIO_AF10_OGT2_HS     GPIO_AF10_OGT_HS

// Funcio alternativa AF11
// Funcio ETH
#define HAL_GPIO_AF11_ETH         GPIO_AF11_ETH

// Funcio alternativa AF12
// -Funcio FMC
#define HAL_GPIO_AF12_FMC         GPIO_AF12_FMC
// -Funcio OGTx
#define HAL_GPIO_AF12_OGT2_FS     GPIO_AF12_OTG_HS_FS
// -Funcio SDMMC
#define HAL_GPIO_AF12_SDMMC1      GPIO_AF12_SDMMC1

// Funcio alternativa AF13
// -Funcio DCMI
#define HAL_GPIO_AF13_DCMI        GPIO_AF13_DCMI

// Funcio alternativa AF14
// -Funcio LTDC
#define HAL_GPIO_AF14_LTDC        GPIO_AF14_LTDC


// Tipus de port
#define HAL_GPIO_MODE_pos         0u
#define HAL_GPIO_MODE_bits        0b1111u
#define HAL_GPIO_MODE_mask        (HAL_GPIO_MODE_bits << HAL_GPIO_MODE_pos)

#define HAL_GPIO_MODE_INPUT       (0u << HAL_GPIO_MODE_pos) // -Entrada digital
#define HAL_GPIO_MODE_OUTPUT_PP   (1u << HAL_GPIO_MODE_pos) // -Sortida push-pull
#define HAL_GPIO_MODE_OUTPUT_OD   (2u << HAL_GPIO_MODE_pos) // -Sortida open-drain
#define HAL_GPIO_MODE_ALT_PP      (3u << HAL_GPIO_MODE_pos) // -Sortida alternativa push-pull
#define HAL_GPIO_MODE_ALT_OD      (4u << HAL_GPIO_MODE_pos) // -Sortida alternativa open-drain
#define HAL_GPIO_MODE_ANALOG      (5u << HAL_GPIO_MODE_pos) // -Entrada/Sortida Analogica

// Velocitat de conmutacio
#define HAL_GPIO_SPEED_pos        4u
#define HAL_GPIO_SPEED_bits       0b11u
#define HAL_GPIO_SPEED_mask       (HAL_GPIO_SPEED_bits << HAL_GPIO_SPEED_pos)

#define HAL_GPIO_SPEED_LOW        (0u << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_MEDIUM	  (1u << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_HIGH       (2u << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_FAST       (3u << HAL_GPIO_SPEED_pos)

// Resistencies pull-up
#define HAL_GPIO_PULL_pos         6u
#define HAL_GPIO_PULL_bits        0b11u
#define HAL_GPIO_PULL_mask        (HAL_GPIO_PULL_bits << HAL_GPIO_PULL_pos)

#define HAL_GPIO_PULL_NONE        (0u << HAL_GPIO_PULL_pos)
#define HAL_GPIO_PULL_UP          (1u << HAL_GPIO_PULL_pos)
#define HAL_GPIO_PULL_DOWN        (2u << HAL_GPIO_PULL_pos)

// Valor inicial de la sortida
#define HAL_GPIO_INIT_pos         8u
#define HAL_GPIO_INIT_bits        0b1u
#define HAL_GPIO_INIT_mask        (HAL_GPIO_INIT_bits << HAL_GPIO_INIT_pos)

#define HAL_GPIO_INIT_CLR         (0u << HAL_GPIO_INIT_pos)
#define HAL_GPIO_INIT_SET         (1u << HAL_GPIO_INIT_pos)


#define halGPIOInitializePinInput(port, pin) \
	halGPIOInitializePin(port, pin, HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);

#define halGPIOInitializePinOutput(port, pin) \
	halGPIOInitializePin(port, pin, HAL_GPIO_MODE_OUTPUT_PP, HAL_GPIO_AF_NONE);

#if 1
// Canvi del estat del pin
//
#define halGPIOSetPin(port, pin) \
	gpioTbl[port]->BSRR = ((uint32_t) 1) << (pin)

#define halGPIOClearPin(port, pin) \
	gpioTbl[port]->BSRR = ((uint32_t) 1) << ((pin) + 16)

#define halGPIOTogglePin(port, pin) \
	gpioTbl[port]->ODR ^= ((uint32_t) 1) << (pin)
#endif

// Lectura i escriptura del pin
//
#define halGPIOReadPin(port, pin) \
	((gpioTbl[port]->IDR & (((uint32_t) 1) << (pin))) != 0)

#define halGPIOWritePin(port, pin, data) \
	if (1) {                             \
		if (data)                        \
			halGPIOSetPin(port, pin);    \
	    else                             \
			halGPIOClearPin(port, pin);  \
	}

// Lectura i escriptura del port
//
#define halGPIOWritePort(port, data) \
    gpioTbl[port]->ODR = data

#define halGPIOReadPort(port) \
    gpioTbl[port]->IDR


void halGPIOInitializePins(const GPIOInitializePinInfo* info, unsigned count);
void halGPIOInitializePorts(const GPIOInitializePortInfo* info, unsigned count);
void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIOOptions options, GPIOAlt alt);
void halGPIOInitializePort(GPIOPort port, GPIOMask mask, GPIOOptions options, GPIOAlt alt);

#if 0
void halGPIOClearPin(GPIOPort port, GPIOPin pin);
void halGPIOSetPin(GPIOPort port, GPIOPin pin);
void halGPIOTogglePin(GPIOPort port, GPIOPin pin);
#endif


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halGPIO__

