#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halGPIO.h"


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

static uint32_t enabledPorts = 0; // Indicador dels ports actius


/// ----------------------------------------------------------------------
/// \brief Activa el port GPIO
/// \param port: El identificador del port.
///
static void enableGPIO(
	GPIOPort port) {

	switch (port) {
		case HAL_GPIO_PORT_A:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
			break;

		case HAL_GPIO_PORT_B:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
			break;

		case HAL_GPIO_PORT_C:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
			break;

		case HAL_GPIO_PORT_D:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
			break;

		case HAL_GPIO_PORT_E:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
			break;

		case HAL_GPIO_PORT_F:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
			break;

		case HAL_GPIO_PORT_G:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
			break;

		case HAL_GPIO_PORT_H:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
			break;

		case HAL_GPIO_PORT_I:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
			break;

		case HAL_GPIO_PORT_J:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
			break;

		case HAL_GPIO_PORT_K:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
			break;
	}

	enabledPorts |= 1 << port;
}


/// ----------------------------------------------------------------------
/// \brief Comprova si el port GPIO esta activat.
/// \param port: El identificador del port.
/// \return True si esta activat.
///
static inline bool isEnabledGPIO(
	GPIOPort port) {

	return (enabledPorts & (1 << port)) != 0;
}


/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: El numero de port.
/// \param pin: El numero de pin.
/// \param options: Les opcions de configuracio.
/// \param alt: La funcio alternativa.
///
static void setupPin(
	GPIOPort port,
	GPIOPin pin,
	GPIOOptions options,
	GPIOAlt alt) {

	uint32_t temp;
	GPIO_TypeDef *gpio = gpioTbl[port];

	// Configura el registre AFR (Alternate Funcion Register)
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD)) {
        temp = gpio->AFR[pin >> 3u];
        temp &= ~(0xFU << ((uint32_t)(pin & 0x07U) * 4u)) ;
        temp |= ((uint32_t)(alt) << (((uint32_t)pin & 0x07u) * 4u));
        gpio->AFR[pin >> 3u] = temp;
	}

	// Configura el registre MODER (Mode Register)
	//
	temp = gpio->MODER;
	temp &= ~(0b11u << (pin * 2u));
	switch (options & HAL_GPIO_MODE_mask) {
		// Sortida digital
		case HAL_GPIO_MODE_OUTPUT_PP:
		case HAL_GPIO_MODE_OUTPUT_OD:
			temp |= 0b01u << (pin * 2u);
			break;

		// Funcio alternativa
		case HAL_GPIO_MODE_ALT_PP:
		case HAL_GPIO_MODE_ALT_OD:
			temp |= 0b10u << (pin * 2u);
			break;

		// Entrada analogica
		case HAL_GPIO_MODE_ANALOG:
			temp |= 0b11u << (pin * 2u);
			break;

		// Entrada digital
		case HAL_GPIO_MODE_INPUT:
			break;
	}
	gpio->MODER = temp;

	// Configura el registre OSPEEDR (Output Speed Register)
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD)) {

		temp = gpio->OSPEEDR;
		temp &= ~(0b11u << (pin * 2u));
		switch (options & HAL_GPIO_SPEED_mask) {
			case HAL_GPIO_SPEED_MEDIUM:
				temp |= 0b01u < (pin * 2u);
				break;

			case HAL_GPIO_SPEED_HIGH:
				temp |= 0b10u < (pin * 2u);
				break;

			case HAL_GPIO_SPEED_FAST:
				temp |= 0b11u < (pin * 2u);
				break;
		}
		gpio->OSPEEDR = temp;
	}

	// Configura el registre OTYPER (Output Type Register)
	//
	temp = gpio->OTYPER;
	temp &= ~(1u << pin);
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD) ||
        ((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD))
		temp |= 1u << pin;
	gpio->OTYPER = temp;

	// Configura el registre PUPDR (PullUp PullDown Register)
	//
	temp = gpio->PUPDR;
	temp &= ~(0b11u << (pin * 2u));
	switch (options & HAL_GPIO_PULL_mask) {
		case HAL_GPIO_PULL_UP:
			temp |= 0b01u << (pin * 2u);
			break;

		case HAL_GPIO_PULL_DOWN:
			temp |= 0b10u << (pin * 2u);
			break;
	}
	gpio->PUPDR = temp;

	// Configura el valor pin de sortida
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD)) {

		temp = gpio->BSRR;
		if ((options & HAL_GPIO_INIT_mask) == HAL_GPIO_INIT_SET)
			temp |= 1u << pin;
		else
			temp |= 1u << (pin + 16u);
		gpio->BSRR = temp;
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura una llista de pins.
/// \param pInfo: Llista d'elements de configuracio.
/// \param count: Numero d'elements de la llista.
///
void halGPIOInitializePins(
	const GPIOInitializePinInfo *pInfo,
	unsigned count) {

	eosAssert(pInfo != NULL);
	eosAssert(count != 0);

	for (unsigned i = 0; i < count; i++) {

		const GPIOInitializePinInfo *p = &pInfo[i];

		if (!isEnabledGPIO(p->port))
			enableGPIO(p->port);

		setupPin(p->port, p->pin, p->options, p->alt);
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura una llista de ports.
/// \param pInfo: Llista d'informacio de configuracio.
/// \param count: Numero d'elements de la llista.
///
void halGPIOInitializePorts(
	const GPIOInitializePortInfo *pInfo,
	unsigned count) {

	eosAssert(pInfo != NULL);
	eosAssert(count != 0);

	for (unsigned i = 0; i < count; i++) {

		const GPIOInitializePortInfo *p = &pInfo[i];

		if (!isEnabledGPIO(p->port))
			enableGPIO(p->port);

		for (unsigned pin = 0; pin < 16; pin++)
			if (p->mask & (1u << pin))
				setupPin(p->port, pin, p->options, p->alt);
	}
}


/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: Identificador del port.
/// \param pin: Identificador del pin.
/// \param options: Opcions.
/// \param function: Funcio del pin.
///
void halGPIOInitializePin(
	GPIOPort port,
	GPIOPin pin,
	GPIOOptions options,
	GPIOAlt alt) {

	if (!isEnabledGPIO(port))
		enableGPIO(port);

	setupPin(port, pin, options, alt);
}


/// ----------------------------------------------------------------------
/// \brief Posa un pin al estat inactiu.
/// \param port: El identificador del port.
/// \param pin: El identificador del pin.
///
#if 0
inline void halGPIOClearPin(
	GPIOPort port,
	GPIOPin pin) {

	gpioTbl[port]->BSRR = 1u << (pin + 16);

}
#endif


/// ----------------------------------------------------------------------
/// \brief Posa un pin al estat actiu.
/// \param port: El identificador del port.
/// \param pin: El identificador del pin.
///
#if 0
inline void halGPIOSetPin(
	GPIOPort port,
	GPIOPin pin) {

	gpioTbl[port]->BSRR = 1u << pin;
}
#endif


/// ----------------------------------------------------------------------
/// \brief Inverteix l'estat del pin.
/// \param port: El identificador del port.
/// \param pin: El identificador del pin.
///
#if 0
inline void halGPIOTogglePin(
	GPIOPort port,
	GPIOPin pin) {

	gpioTbl[port]->ODR ^= 1u << pin;
}
#endif
