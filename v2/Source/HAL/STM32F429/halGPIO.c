#include "hal/halGPIO.h"

GPIO_TypeDef *gpioPortRegs[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF,
		GPIOG, GPIOH, GPIOI, GPIOJ, GPIOK };

/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: Identificador del port.
/// \param pin: Identificador del pin.
/// \param direction: Direccio.
///
void halGPIOInitializePin(GPIOPort port, GPIOPin pin, GPIOOptions options) {

	RCC->AHB1ENR |= 1 << port;

	GPIO_TypeDef *p = gpioPortRegs[port];

	if (options & GPIO_DIRECTION_OUTPUT) {
		p->MODER &= ~(0b11 << (pin * 2));
		p->MODER |= 0b01 << (pin * 2);
	}

	if (options & GPIO_OPENDRAIN_ENABLED)
		p->OTYPER |= 1 << pin;
	else
		p->OTYPER &= ~(1 << pin);
}

/// ----------------------------------------------------------------------
/// \brief Configura un port.
/// \param port: El handler del port.
/// \param direction: Direccio.
/// \param mask: Mascara.
///
void halGPIOInitializePort(GPIOPort port, GPIOOptions options, uint16_t mask) {

	RCC->AHB1ENR |= 1 << port;
}
