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
/// \brief Configura un pin individual.
/// \param info: Informacio de configuracio.
///
void halGPIOInitializePin(
	const GPIOInitializePinInfo *info) {

	uint32_t temp;
	GPIO_TypeDef * const gpio = gpioTbl[info->port];

	// Activa el rellotge del controlador GPIO
	//
	RCC->AHB1ENR |= 1 << info->port;

	// Selecciona el modus (INPUT, OUTPUT, ANALOG, FUNCTION)
	//
	temp = gpio->MODER;
	temp &= ~(0b11 << (info->pin * 2)); // Per defecte INPUT
	switch (info->options & HAL_GPIO_MODE_MASK) {
		case HAL_GPIO_MODE_OUTPUT:
			temp |= 0b01 << (info->pin * 2);
			if ((info->options & HAL_GPIO_INIT_MASK) == HAL_GPIO_INIT_CLR)
				halGPIOClearPin(info->port, info->pin);
			else
				halGPIOSetPin(info->port, info->pin);
			break;

		case HAL_GPIO_MODE_FUNCTION:
			temp |= 0b10 << (info->pin * 2);
			break;

		case HAL_GPIO_MODE_ANALOG:
			temp |= 0b11 << (info->pin * 2);
			break;
	}
	gpio->MODER = temp;

	// Selecciona el PullUp (NONE, UP, DOWN)
	//
	temp = gpio->PUPDR;
	temp &= ~(0b11 << (info->pin * 2)); // Per defecte NONE
	switch (info->options & HAL_GPIO_PULL_MASK) {
		case HAL_GPIO_PULL_UP:
			temp |= 0b01 << (2 * info->pin);
			break;

		case HAL_GPIO_PULL_DOWN:
			temp |= 0b10 << ( 2 * info->pin);
			break;
	}
	gpio->PUPDR = temp;

	// En cas que sigui MODE_OUTPUT o MODE_FUNCTION
	//
	if  (((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT) ||
		 ((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_FUNCTION)) {

		// Selecciona la velocitat (LOW, MEDIUM, HIGH, FAST)
		//
		temp = gpio->OSPEEDR;
		temp &= ~(0b11 << (2 * info->pin)); // Per defecte LOW
		switch (info->options & HAL_GPIO_SPEED_MASK) {
			case HAL_GPIO_SPEED_MEDIUM:
				temp |= 0b01 << (2 * info->pin);
				break;

			case HAL_GPIO_SPEED_HIGH:
				temp |= 0b10 << (2 * info->pin);
				break;

			case HAL_GPIO_SPEED_FAST:
				temp |= 0b11 << (2 * info->pin);
				break;
		}
		gpio->OSPEEDR = temp;

		// Selecciona el tipus de sortida (PUSHPULL, OPENDRAIN)
		//
		temp = gpio->OTYPER;
		if ((info->options & HAL_GPIO_OPENDRAIN_MASK) == HAL_GPIO_OPENDRAIN_ENABLED)
			temp |= 1 << info->pin;
		else
			temp &= ~(1 << info->pin);
		gpio->OTYPER = temp;
	}

	// Si es una funcio alternativa, la selecciona
	//
	if ((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_FUNCTION) {
		temp = gpio->AFR[info->pin >> 3];
	    temp &= ~((uint32_t)0xFU << ((uint32_t)(info->pin & (uint32_t)0x07U) * 4U)) ;
	    temp |= ((uint32_t)info->function << (((uint32_t)info->pin & (uint32_t)0x07U) * 4U));
	    gpio->AFR[info->pin >> 3] = temp;
	}

	// Si es una sortida digital, inicialitza el seu valor
	//
	if ((info->options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_OUTPUT) {
		if ((info->options & HAL_GPIO_INIT_MASK) == HAL_GPIO_INIT_CLR)
			halGPIOClearPin(info->port, info->pin);
		else
			halGPIOSetPin(info->port, info->pin);
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
/// \brief Configura un port individual.
/// \param info: Informacio de configuracio.
///
void halGPIOInitializePort(
	const GPIOInitializePortInfo *info) {

	GPIOInitializePinInfo pinInfo;
	pinInfo.port = info->port;
	pinInfo.options = info->options;
	pinInfo.function = info->function;

	for (uint8_t pin = 0; pin < 16; pin++) {
		if ((info->mask & (1 << pin)) != 0) {
			pinInfo.pin = pin;
			halGPIOInitializePin(&pinInfo);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura un port com a entrades.
/// \param port: Identificador del port.
/// \param mask: Mascara de pins.
///
void halGPIOInitializePortInput(
	uint8_t port,
	uint16_t mask) {

	GPIOInitializePinInfo info;
	info.port = port;
	info.options = HAL_GPIO_MODE_INPUT;
	info.function = 0;

	for (uint8_t pin = 0; pin < 16; pin++) {
		if ((mask & (1 << pin)) != 0) {
			info.pin = pin;
			halGPIOInitializePin(&info);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura un port com a sortides.
/// \param port: Identificador del port.
/// \param mask: Mascara de pins.
///
void halGPIOInitializePortOutput(
	uint8_t port,
	uint16_t mask) {

	GPIOInitializePinInfo info;
	info.port = port;
	info.options = HAL_GPIO_MODE_OUTPUT;
	info.function = 0;

	for (uint8_t pin = 0; pin < 16; pin++) {
		if ((mask & (1 << pin)) != 0) {
			info.pin = pin;
			halGPIOInitializePin(&info);
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: Identificador del port.
/// \param pin: Identificador del pin.
/// \param options: Opcions.
/// \param function: Funcio del pin.
///
void halGPIOInitialize(
	uint8_t port,
	uint8_t pin,
	uint32_t options,
	GPIOFunction function) {

	GPIOInitializePinInfo init;
	init.port = port;
	init.pin = pin;
	init.options = options;
	init.function = function;

	halGPIOInitializePin(&init);
}
