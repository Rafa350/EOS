#include "hal/halGPIO.h"


GPIO_TypeDef * const gpioTbl[] = {
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
/// \brief Configura una llista de pins.
/// \param info: Llista d'informacio de configuracio.
/// \param count: Numero d'elements de la llista.
///
void halGPIOInitializePins(
	const GPIOInitializePinInfo *info,
	uint8_t count) {

	for (uint8_t i = 0; i < count; i++)
		halGPIOInitializePin(&info[i]);
}


/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param info: Informacio de configuracio.
///
void halGPIOInitializePin(
	const GPIOInitializePinInfo *info) {

	halGPIOInitialize(info->port, info->pin, info->options, info->function);
}


/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: Identificador del port.
/// \param pin: Identificador del pin.
/// \param options: Opcions.
/// \param function: Funcio del pin.
///
void halGPIOInitialize(
	GPIOPort port,
	GPIOPin pin,
	GPIOOptions options,
	GPIOFunction function) {

	uint32_t temp;
	GPIO_TypeDef * const gpio = gpioTbl[port];

	// Activa el rellotge del controlador GPIO
	//
	RCC->AHB1ENR |= 1 << port;

	// Selecciona el modus (INPUT, OUTPUT, ANALOG, FUNCTION)
	//
	temp = gpio->MODER;
	temp &= ~(0b11 << (pin * 2)); // Per defecte INPUT
	switch (options & HAL_GPIO_MODE_MASK) {
		case HAL_GPIO_MODE_OUTPUT:
			temp |= 0b01 << (pin * 2);
			break;

		case HAL_GPIO_MODE_FUNCTION:
			temp |= 0b10 << (pin * 2);
			break;

		case HAL_GPIO_MODE_ANALOG:
			temp |= 0b11 << (pin * 2);
			break;
	}
	gpio->MODER = temp;

	// Selecciona el PullUp (NONE, UP, DOWN)
	//
	temp = gpio->PUPDR;
	temp &= ~(0b11 << (pin * 2)); // Per defecte NONE
	switch (options & HAL_GPIO_PULL_MASK) {
		case HAL_GPIO_PULL_UP:
			temp |= 0b01 << (2 * pin);
			break;

		case HAL_GPIO_PULL_DOWN:
			temp |= 0b10 << ( 2 * pin);
			break;
	}
	gpio->PUPDR = temp;

	// En cas que sigui MODE_OUTPUT o MODE_FUNCTION
	//
	if  (((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT) ||
		 ((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_FUNCTION)) {

		// Selecciona la velocitat (LOW, MEDIUM, HIGH, FAST)
		//
		temp = gpio->OSPEEDR;
		temp &= ~(0b11 << (2 * pin)); // Per defecte LOW
		switch (options & HAL_GPIO_SPEED_MASK) {
			case HAL_GPIO_SPEED_MEDIUM:
				temp |= 0b01 << (2 * pin);
				break;

			case HAL_GPIO_SPEED_HIGH:
				temp |= 0b10 << (2 * pin);
				break;

			case HAL_GPIO_SPEED_FAST:
				temp |= 0b11 << (2 * pin);
				break;
		}
		gpio->OSPEEDR = temp;

		// Selecciona el tipus de sortida (PUSHPULL, OPENDRAIN)
		//
		temp = gpio->OTYPER;
		if ((options & HAL_GPIO_OPENDRAIN_MASK) == HAL_GPIO_OPENDRAIN_ENABLED)
			temp |= 1 << pin;
		else
			temp &= ~(1 << pin);
		gpio->OTYPER = temp;
	}

	// Selecciona la funcio alternativa
	//
	if ((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_FUNCTION) {
		temp = gpio->AFR[pin >> 3];
	    temp &= ~((uint32_t)0xFU << ((uint32_t)(pin & (uint32_t)0x07U) * 4U)) ;
	    temp |= ((uint32_t)function << (((uint32_t)pin & (uint32_t)0x07U) * 4U));
	    gpio->AFR[pin >> 3] = temp;
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura una llista de ports.
/// \param info: Llista d'informacio de confiuguracio.
/// \param count: Numero d'elements de la llista.
///
void halGPIOInitializePorts(
	const GPIOInitializePortInfo *info,
	uint8_t count) {

	for (uint8_t i = 0; i < count; i++)
		halGPIOInitializePort(&info[i]);
}


/// ----------------------------------------------------------------------
/// \brief Configura un port.
/// \param info: Informacio de configuracio.
///
void halGPIOInitializePort(
	const GPIOInitializePortInfo *info) {

	for (uint8_t pin = 0; pin < 16; pin++) {
		if ((info->mask & (1 << pin)) != 0)
			halGPIOInitialize(info->port, pin, info->options, info->function);
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
		if ((mask & (1 << pin)) != 0)
			halGPIOInitialize(port, pin, HAL_GPIO_MODE_INPUT, 0);
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
		if ((mask & (1 << pin)) != 0)
			halGPIOInitialize(port, pin, HAL_GPIO_MODE_OUTPUT, 0);
	}
}
