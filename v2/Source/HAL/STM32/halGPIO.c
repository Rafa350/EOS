#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halGPIO.h"


/// ----------------------------------------------------------------------
/// \brief    Activa el clock del port GPIO
/// \param    port: Identificador del port.
///
static void enablePeripheralClock(
	GPIOPort port) {

	eosAssert(IS_GPIO_ALL_INSTANCE(port));

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
}


/// ----------------------------------------------------------------------
/// \brief    Configura un pin.
/// \param    port: Identificador del port.
/// \param    pin: Numero de pin.
/// \param    options: Opcions de configuracio.
/// \param    alt: Funcio alternativa.
///
static void setupPin(
	GPIOPort port,
	GPIOPin pin,
	GPIOOptions options,
	GPIOAlt alt) {

	eosAssert(IS_GPIO_ALL_INSTANCE(port));
	eosAssert((pin >= 0) && (pin <= 15));

	uint32_t temp;
	GPIORegisters* regs = (GPIORegisters*) port;

	// Configura el registre MODER (Mode Register)
	//
	temp = regs->MODER;
	temp &= ~(0b11 << (pin * 2));
	switch (options & HAL_GPIO_MODE_mask) {
		// Sortida digital
		case HAL_GPIO_MODE_OUTPUT_PP:
		case HAL_GPIO_MODE_OUTPUT_OD:
			temp |= 0b01 << (pin * 2);
			break;

		// Funcio alternativa
		case HAL_GPIO_MODE_ALT_PP:
		case HAL_GPIO_MODE_ALT_OD:
			temp |= 0b10 << (pin * 2);
			break;

		// Entrada analogica
		case HAL_GPIO_MODE_ANALOG:
			temp |= 0b11 << (pin * 2);
			break;

		// Entrada digital
		case HAL_GPIO_MODE_INPUT:
			break;
	}
	regs->MODER = temp;

	// Configura el registre AFR (Alternate Funcion Register)
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD)) {
	    temp = regs->AFR[pin >> 3];
	    temp &= ~(0x0F << ((uint32_t)(pin & 0x07) * 4)) ;
        temp |= ((uint32_t)(alt) << (((uint32_t)pin & 0x07) * 4));
        regs->AFR[pin >> 3] = temp;
	}

	// Configura el registre OSPEEDR (Output Speed Register)
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD)) {

		temp = regs->OSPEEDR;
		temp &= ~(0b11 << (pin * 2));
		switch (options & HAL_GPIO_SPEED_mask) {
			case HAL_GPIO_SPEED_MEDIUM:
				temp |= 0b01 < (pin * 2);
				break;

			case HAL_GPIO_SPEED_HIGH:
				temp |= 0b10 < (pin * 2);
				break;

			case HAL_GPIO_SPEED_FAST:
				temp |= 0b11u < (pin * 2);
				break;
		}
		regs->OSPEEDR = temp;
	}

	// Configura el registre OTYPER (Output Type Register)
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD)) {
		temp = regs->OTYPER;
		temp &= ~(1u << pin);
		if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD) ||
			((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD))
			temp |= 1 << pin;
		regs->OTYPER = temp;
	}

	// Configura el registre PUPDR (Pull Up/Down Register)
	//
	if ((options & HAL_GPIO_MODE_mask) != HAL_GPIO_MODE_ANALOG) {
		temp = regs->PUPDR;
		temp &= ~(0b11 << (pin * 2u));
		switch (options & HAL_GPIO_PULL_mask) {
			case HAL_GPIO_PULL_UP:
				temp |= 0b01 << (pin * 2);
				break;

			case HAL_GPIO_PULL_DOWN:
				temp |= 0b10 << (pin * 2);
				break;
		}
		regs->PUPDR = temp;
	}

	// Configura el valor inicial pin de sortida
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD)) {

		temp = regs->BSRR;
		if ((options & HAL_GPIO_INIT_mask) == HAL_GPIO_INIT_SET)
			temp |= 1 << pin;
		else
			temp |= 1 << (pin + 16);
		regs->BSRR = temp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Configura una llista de pins.
/// \param    info: Llista d'elements de configuracio.
/// \param    count: Numero d'elements de la llista.
///
void halGPIOInitializePins(
	const GPIOInitializePinInfo *info,
	uint32_t count) {

	eosAssert(info != NULL);
	eosAssert(count != 0);

	for (uint32_t i = 0; i < count; i++) {

		const GPIOInitializePinInfo* p = &info[i];

		enablePeripheralClock(p->port);
		setupPin(p->port, p->pin, p->options, p->alt);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Configura una llista de ports.
/// \param    info: Llista d'elements de configuracio.
/// \param    count: Numero d'elements de la llista.
///
void halGPIOInitializePorts(
	const GPIOInitializePortInfo* info,
	uint32_t count) {

	eosAssert(info != NULL);
	eosAssert(count != 0);

	for (uint32_t i = 0; i < count; i++) {

		const GPIOInitializePortInfo* p = &info[i];

		enablePeripheralClock(p->port);

		for (GPIOPin pin = 0; pin < 16; pin++)
			if (p->mask & (1 << pin))
				setupPin(p->port, pin, p->options, p->alt);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Configura un pin.
/// \param    port: Identificador del port.
/// \param    pin: Identificador del pin.
/// \param    options: Opcions.
/// \param    alt: Funcio alternativa.
///
void halGPIOInitializePin(
	GPIOPort port,
	GPIOPin pin,
	GPIOOptions options,
	GPIOAlt alt) {

	eosAssert(IS_GPIO_ALL_INSTANCE(port));
	eosAssert((pin >= 0) && (pin <= 15));

	enablePeripheralClock(port);

	setupPin(port, pin, options, alt);
}


/// ----------------------------------------------------------------------
/// \brief    Posa un pin al estat inactiu.
/// \param    port: Identificador del port.
/// \param    pin: Numero de pin.
///
#if HAL_GPIO_INLINE == 0
inline void halGPIOClearPin(
	GPIOPort port,
	GPIOPin pin) {

	eosAssert(IS_GPIO_ALL_INSTANCE(port));
	eosAssert((pin >= 0) && (pin <= 15));

	((GPIORegisters*)port)->BSRR = 1u << (pin + 16);

}
#endif


/// ----------------------------------------------------------------------
/// \brief    Posa un pin al estat actiu.
/// \param    port: Identificador del port.
/// \param    pin: Numero de pin.
///
#if HAL_GPIO_INLINE == 0
inline void halGPIOSetPin(
	GPIOPort port,
	GPIOPin pin) {

	eosAssert(IS_GPIO_ALL_INSTANCE(port));
	eosAssert((pin >= 0) && (pin <= 15));

	((GPIORegisters*)port)->BSRR = 1u << pin;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat del pin.
/// \param    port: Identificador del port.
/// \param    pin: Numero de pin.
///
#if HAL_GPIO_INLINE == 0
inline void halGPIOTogglePin(
	GPIOPort port,
	GPIOPin pin) {

	eosAssert(IS_GPIO_ALL_INSTANCE(port));
	eosAssert((pin >= 0) && (pin <= 15));

	((GPIORegisters*)port)->ODR ^= 1u << pin;
}
#endif
