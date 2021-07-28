/// \file      halGPIO.h
/// \author    Rafael Serrano (rsr.openware@gmail.com)
/// \brief     GPIO module manager.
/// \addtogroup HAL Hardware Abstraction Layer
/// @{
/// \addtogroup HAL_STM32 STM32 Hardware Abstraction Layer
/// @{
/// \defgroup HAL_STM32_GPIO GPIO
/// @{
///
#ifndef __STM32_halGPIO__
#define	__STM32_halGPIO__


// HAL includes
//
#include "HAL/hal.h"
#if defined(EOS_STM32F4)
	#include "HAL/STM32/halGPIO_F4xx.h"
#elif defined(EOS_STM32F7)
	#include "HAL/STM32/halGPIO_F7xx.h"
#endif

// STM32 includes
//
#if defined(EOS_STM32F4)
	#include "stm32f4xx_hal_gpio_ex.h"
#elif defined(EOS_STM32F7)
	#include "stm32f7xx_hal_gpio_ex.h"
#else
	#error Hardware no soportado
#endif


// Opcions del modul
//
#define HAL_GPIO_INLINE           1    ///< Use macro functions for performance


#ifdef	__cplusplus
extern "C" {
#endif


typedef uint32_t GPIOPort;        ///< Port identifier.
typedef uint32_t GPIOPin;         ///< Pin number.
typedef uint32_t GPIOMask;        ///< Position pin mask.
typedef uint32_t GPIOOptions;     ///< Pin options.
typedef uint32_t GPIOAlt;         ///< Alternate pin function.

/// \brief GPIO pin initialization parameters.
typedef struct {
	GPIOPort port;                ///< Port identifier.
	GPIOPin pin;                  ///< Pin identifier
	GPIOOptions options;          ///< Options
	GPIOAlt alt;                  ///< Alternate pin function
} GPIOPinSettings;

/// \brief GPIO port initialization parameters
typedef struct {
	GPIOPort port;                ///< Port identifier.
	GPIOMask mask;                ///< Selection pin mask.
	GPIOOptions options;          ///< Options.
	GPIOAlt alt;                  ///< Alternate pin function.
} GPIOPortSettings;


// Identificado del port
#define HAL_GPIO_PORT_A           GPIOA_BASE
#define HAL_GPIO_PORT_B           GPIOB_BASE
#define HAL_GPIO_PORT_C           GPIOC_BASE
#define HAL_GPIO_PORT_D           GPIOD_BASE
#define HAL_GPIO_PORT_E           GPIOE_BASE
#define HAL_GPIO_PORT_F           GPIOF_BASE
#define HAL_GPIO_PORT_G           GPIOG_BASE
#define HAL_GPIO_PORT_H           GPIOH_BASE
#define HAL_GPIO_PORT_I           GPIOI_BASE
#define HAL_GPIO_PORT_J           GPIOJ_BASE
#define HAL_GPIO_PORT_K           GPIOK_BASE
#define HAL_GPIO_PORT_NONE        0

// Identificador del pin
#define HAL_GPIO_PIN_0            0
#define HAL_GPIO_PIN_1            1
#define HAL_GPIO_PIN_2            2
#define HAL_GPIO_PIN_3            3
#define HAL_GPIO_PIN_4            4
#define HAL_GPIO_PIN_5            5
#define HAL_GPIO_PIN_6            6
#define HAL_GPIO_PIN_7            7
#define HAL_GPIO_PIN_8            8
#define HAL_GPIO_PIN_9            9
#define HAL_GPIO_PIN_10           10
#define HAL_GPIO_PIN_11           11
#define HAL_GPIO_PIN_12           12
#define HAL_GPIO_PIN_13           13
#define HAL_GPIO_PIN_14           14
#define HAL_GPIO_PIN_15           15
#define HAL_GPIO_PIN_NONE         255

// Identificador de la funcio alternativa
#define HAL_GPIO_AF_0             0
#define HAL_GPIO_AF_1             1
#define HAL_GPIO_AF_2             2
#define HAL_GPIO_AF_3             3
#define HAL_GPIO_AF_4             4
#define HAL_GPIO_AF_5             5
#define HAL_GPIO_AF_6             6
#define HAL_GPIO_AF_7             7
#define HAL_GPIO_AF_8             8
#define HAL_GPIO_AF_9             9
#define HAL_GPIO_AF_10            10
#define HAL_GPIO_AF_11            11
#define HAL_GPIO_AF_12            12
#define HAL_GPIO_AF_13            13
#define HAL_GPIO_AF_14            14
#define HAL_GPIO_AF_15            15
#define HAL_GPIO_AF_NONE          HAL_GPIO_AF_0


// Mascara de posicio del pin
#define HAL_GPIO_POS_0            (1 << 0)
#define HAL_GPIO_POS_1            (1 << 1)
#define HAL_GPIO_POS_2            (1 << 2)
#define HAL_GPIO_POS_3            (1 << 3)
#define HAL_GPIO_POS_4            (1 << 4)
#define HAL_GPIO_POS_5            (1 << 5)
#define HAL_GPIO_POS_6            (1 << 6)
#define HAL_GPIO_POS_7            (1 << 7)
#define HAL_GPIO_POS_8            (1 << 8)
#define HAL_GPIO_POS_9            (1 << 9)
#define HAL_GPIO_POS_10           (1 << 10)
#define HAL_GPIO_POS_11           (1 << 11)
#define HAL_GPIO_POS_12           (1 << 12)
#define HAL_GPIO_POS_13           (1 << 13)
#define HAL_GPIO_POS_14           (1 << 14)
#define HAL_GPIO_POS_15           (1 << 15)
#define HAL_GPIO_POS_LO           0x000000FF
#define HAL_GPIO_POS_HI           0x0000FF00
#define HAL_GPIO_POS_ALL          0x0000FFFF

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

// Funcio alternativa AF8
// -Funcio USART
#define HAL_GPIO_AF8_USART6       GPIO_AF8_USART6

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
#define HAL_GPIO_MODE_pos         0
#define HAL_GPIO_MODE_bits        0b1111
#define HAL_GPIO_MODE_mask        (HAL_GPIO_MODE_bits << HAL_GPIO_MODE_pos)

#define HAL_GPIO_MODE_INPUT       (0 << HAL_GPIO_MODE_pos) // -Entrada digital (Sempre es entrada
#define HAL_GPIO_MODE_OUTPUT_PP   (1 << HAL_GPIO_MODE_pos) // -Sortida push-pull
#define HAL_GPIO_MODE_OUTPUT_OD   (2 << HAL_GPIO_MODE_pos) // -Sortida open-drain
#define HAL_GPIO_MODE_ALT_PP      (3 << HAL_GPIO_MODE_pos) // -Sortida alternativa push-pull
#define HAL_GPIO_MODE_ALT_OD      (4 << HAL_GPIO_MODE_pos) // -Sortida alternativa open-drain
#define HAL_GPIO_MODE_ANALOG      (5 << HAL_GPIO_MODE_pos) // -Entrada/Sortida Analogica

// Velocitat de conmutacio
#define HAL_GPIO_SPEED_pos        4
#define HAL_GPIO_SPEED_bits       0b11
#define HAL_GPIO_SPEED_mask       (HAL_GPIO_SPEED_bits << HAL_GPIO_SPEED_pos)

#define HAL_GPIO_SPEED_LOW        (0 << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_MEDIUM	  (1 << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_HIGH       (2 << HAL_GPIO_SPEED_pos)
#define HAL_GPIO_SPEED_FAST       (3 << HAL_GPIO_SPEED_pos)

// Resistencies pull-up
#define HAL_GPIO_PULL_pos         6
#define HAL_GPIO_PULL_bits        0b11
#define HAL_GPIO_PULL_mask        (HAL_GPIO_PULL_bits << HAL_GPIO_PULL_pos)

#define HAL_GPIO_PULL_NONE        (0 << HAL_GPIO_PULL_pos)
#define HAL_GPIO_PULL_UP          (1 << HAL_GPIO_PULL_pos)
#define HAL_GPIO_PULL_DOWN        (2 << HAL_GPIO_PULL_pos)

// Valor inicial de la sortida
#define HAL_GPIO_INIT_pos         8
#define HAL_GPIO_INIT_bits        0b1
#define HAL_GPIO_INIT_mask        (HAL_GPIO_INIT_bits << HAL_GPIO_INIT_pos)

#define HAL_GPIO_INIT_CLR         (0 << HAL_GPIO_INIT_pos)
#define HAL_GPIO_INIT_SET         (1 << HAL_GPIO_INIT_pos)


#define halGPIOInitializePinInput(port, pin) \
	halGPIOInitializePin(port, pin, HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);

#define halGPIOInitializePinOutput(port, pin) \
	halGPIOInitializePin(port, pin, HAL_GPIO_MODE_OUTPUT_PP, HAL_GPIO_AF_NONE);

#if HAL_GPIO_INLINE == 1
// Canvi del estat del pin
//
#define halGPIOSetPin(port, pin) \
	((GPIO_TypeDef*)port)->BSRR = ((uint32_t) 1) << (pin)

#define halGPIOClearPin(port, pin) \
	((GPIO_TypeDef*)port)->BSRR = ((uint32_t) 1) << ((pin) + 16)

#define halGPIOTogglePin(port, pin) \
	((GPIO_TypeDef*)port)->ODR ^= ((uint32_t) 1) << (pin)
#endif

// Lectura i escriptura del pin
//
#define halGPIOReadPin(port, pin) \
	((((GPIO_TypeDef*)port)->IDR & (((uint32_t) 1) << (pin))) != 0)

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
	((GPIO_TypeDef*)port)->ODR = data

#define halGPIOReadPort(port) \
	((GPIO_TypeDef*)port)->IDR


void halGPIOInitializePins(const GPIOPinSettings* settings, int count);
void halGPIOInitializePorts(const GPIOPortSettings* settings, int count);
void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIOOptions options, GPIOAlt alt);
void halGPIOInitializePort(GPIOPort port, GPIOMask mask, GPIOOptions options, GPIOAlt alt);

#if HAL_GPIO_INLINE == 0
void halGPIOClearPin(GPIOPort port, GPIOPin pin);
void halGPIOSetPin(GPIOPort port, GPIOPin pin);
void halGPIOTogglePin(GPIOPort port, GPIOPin pin);
#endif


#ifdef	__cplusplus
}
#endif


#endif // __STM32_halGPIO__

/// @}
/// @}
/// @}
