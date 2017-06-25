#include "hal/halGPIO.h"


GPIO_TypeDef *gpioTbl[] = {
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

	for (uint8_t i = 0; i < count; i++) {
		GPIOInitializeInfo *p = &info[i];
		halGPIOInitializePin(p->port, p->pin, p->options);
		if ((p->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_ALTERNATE)
			halGPIOInitializeAlternatePin(p->port, p->pin, p->alternate);
	}
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

	GPIO_TypeDef *gpio = gpioTbl[port];

	gpio->MODER &= ~(0b11 << (pin * 2)); // Per defecte INPUT
	switch (options & HAL_GPIO_MODE_MASK) {
		case HAL_GPIO_MODE_OUTPUT:
			gpio->MODER |= 0b01 << (pin * 2);
			break;

		case HAL_GPIO_MODE_ALTERNATE:
			gpio->MODER |= 0b10 << (pin * 2);
			break;

		case HAL_GPIO_MODE_ANALOG:
			gpio->MODER |= 0b11 << (pin * 2);
			break;
	}

	gpio->PUPDR &= ~(0b11 << (pin * 2)); // Per defecte NONE
	switch (options & HAL_GPIO_PULLUPDN_MASK) {
		case HAL_GPIO_PULLUPDN_UP:
			gpio->PUPDR |= 0b01 << (2 * pin);
			break;

		case HAL_GPIO_PULLUPDN_DOWN:
			gpio->PUPDR |= 0b10 << ( 2 * pin);
			break;
	}

	gpio->OSPEEDR &= ~(0b11 << (2 * pin)); // Per defecte LOW
	switch (options & HAL_GPIO_SPEED_MASK) {
		case HAL_GPIO_SPEED_MEDIUM:
			gpio->OSPEEDR |= 0b01 << (2 * pin);
			break;

		case HAL_GPIO_SPEED_HIGH:
			gpio->OSPEEDR |= 0b10 << (2 * pin);
			break;

		case HAL_GPIO_SPEED_FAST:
			gpio->OSPEEDR |= 0b11 << (2 * pin);
			break;
	}

	if ((options & HAL_GPIO_OPENDRAIN_MASK) == HAL_GPIO_OPENDRAIN_ENABLED)
		gpio->OTYPER |= 1 << pin;
	else
		gpio->OTYPER &= ~(1 << pin);
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
