#include "hal/halGPIO.h"


GPIO_TypeDef *gpioPortRegs[] = {
    GPIOA,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	GPIOH,
	GPIOI,
	GPIOJ,
	GPIOK
};


/// ----------------------------------------------------------------------
/// \brief Configura els pins.
/// \param info: Taula d'informacio de configuracio.
/// \param count: Numero d'elements de la taula de configuracio.
///
void halGPIOInitialize(
	GPIOInitializeInfo *info,
	uint8_t count) {

}


/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: Identificador del port.
/// \param pin: Identificador del pin.
/// \param options: Opcions
///
void halGPIOInitializePin(
	GPIOPort port,
	GPIOPin pin,
	GPIOOptions options) {

	RCC->AHB1ENR |= 1 << port;

	GPIO_TypeDef *p = gpioPortRegs[port];

	p->MODER &= ~(0b11 << (pin * 2));
	switch (options & HAL_GPIO_MODE_MASK) {
		case HAL_GPIO_MODE_INPUT:
			p->MODER |= 0b00 << (pin * 2);
			break;

		case HAL_GPIO_MODE_OUTPUT:
			p->MODER |= 0b01 << (pin * 2);
			break;

		case HAL_GPIO_MODE_AF:
			p->MODER |= 0b10 << (pin * 2);
			break;

		case HAL_GPIO_MODE_ANALOG:
			p->MODER |= 0b11 << (pin * 2);
			break;
	}

	p->PUPDR &= ~(1 << (pin * 2));
	switch (options & HAL_GPIO_PULLUPDN_MASK) {
		case HAL_GPIO_PULLUPDN_UP:
			p->PUPDR |= 0b01 << (2 * pin);
			break;

		case HAL_GPIO_PULLUPDN_DOWN:
			p->PUPDR |= 0b10 << ( 2 * pin);
			break;
	}

	p->OSPEEDR &= ~(1 << (2 * pin));
	switch (options & HAL_GPIO_SPEED_MASK) {
		case HAL_GPIO_SPEED_MEDIUM:
			p->OSPEEDR |= 0b01 << (2 * pin);
			break;

		case HAL_GPIO_SPEED_FAST:
			p->OSPEEDR |= 0b11 << (2 * pin);
			break;

		case HAL_GPIO_SPEED_HIGH:
			p->OSPEEDR |= 0b10 << (2 * pin);
			break;
	}

	if ((options & HAL_GPIO_OPENDRAIN_MASK) == HAL_GPIO_OPENDRAIN_ENABLED)
		p->OTYPER |= 1 << pin;
	else
		p->OTYPER &= ~(1 << pin);
}


/// ----------------------------------------------------------------------
/// \brief Configura un port.
/// \param port: El handler del port.
/// \param options: Opcions.
/// \param mask: Mascara.
///
void halGPIOInitializePort(
	GPIOPort port,
	GPIOOptions options,
	uint16_t mask) {

	for (uint8_t pin = 0; pin < 16; pin++) {

		if ((mask & (1 << pin)) != 0)
			halGPIOInitializePin(port, pin , options);
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura un port com a entrades.
/// \param port: Identificador del port.
/// \param mask: Mascara de pins.
///
void halGPIOInitializePortInput(
	GPIOPort port,
	uint16_t mask) {

	for (uint8_t pin = 0; pin < 16; pin++) {

	}
}


/// ----------------------------------------------------------------------
/// \brief Configura un port com a sortides.
/// \param port: Identificador del port.
/// \param mask: Mascara de pins.
///
void halGPIOInitializePortOutput(
	GPIOPort port,
	uint16_t mask) {

	for (uint8_t pin = 0; pin < 16; pin++) {

	}
}
