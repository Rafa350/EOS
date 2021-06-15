#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halGPIO.h"


#define __VERIFY_DEVICE(device)   eosAssert(IS_GPIO_ALL_INSTANCE(device))
#define __VERIFY_PORT(port)       eosAssert(IS_GPIO_ALL_INSTANCE(((GPIO_TypeDef*)port)))
#define __VERIFY_PIN(pin)   	  eosAssert((pin >= 0) && (pin <= 15))


/// ----------------------------------------------------------------------
/// \brief    Obte el dispositiu.
/// \param    port: El identificador del dispositiu.
/// \return   El dispositiu.
///
static inline GPIO_TypeDef* getDevice(
	GPIOPort port) {

	__VERIFY_PORT(port);

	return (GPIO_TypeDef*) port;
}


/// ----------------------------------------------------------------------
/// \brief    Enable device GPIO clock
/// \param    device: Device.
///
static void enableDeviceClock(
	GPIO_TypeDef* device) {

	__VERIFY_DEVICE(device);

	switch ((uint32_t) device) {
		case GPIOA_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
			break;

		case GPIOB_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
			break;

		case GPIOC_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
			break;

		case GPIOD_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
			break;

		case GPIOE_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
			break;

		case GPIOF_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);
			break;

		case GPIOG_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
			break;

		case GPIOH_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);
			break;

		case GPIOI_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);
			break;

		case GPIOJ_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN);
			break;

		case GPIOK_BASE:
			__set_bit_msk(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN);
			break;
	}
	__DSB();
}


/// ----------------------------------------------------------------------
/// \brief    Setup device pin.
/// \param    device: Device.
/// \param    pin: Pun number.
/// \param    options: Pin settings.
/// \param    alt: Alternate piu function.
///
static void setupDevicePin(
	GPIO_TypeDef* device,
	GPIOPin pin,
	GPIOOptions options,
	GPIOAlt alt) {

	__VERIFY_DEVICE(device);
	__VERIFY_PIN(pin);

	uint32_t temp;

	// Configura el registre MODER (Mode Register)
	//
	temp = device->MODER;
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
	device->MODER = temp;

	// Configura el registre AFR (Alternate Funcion Register)
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD)) {
	    temp = device->AFR[pin >> 3];
	    temp &= ~(0x0F << ((uint32_t)(pin & 0x07) * 4)) ;
        temp |= ((uint32_t)(alt) << (((uint32_t)pin & 0x07) * 4));
        device->AFR[pin >> 3] = temp;
	}

	// Configura el registre OSPEEDR (Output Speed Register)
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD)) {

		temp = device->OSPEEDR;
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
		device->OSPEEDR = temp;
	}

	// Configura el registre OTYPER (Output Type Register)
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD)) {
		temp = device->OTYPER;
		temp &= ~(1u << pin);
		if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD) ||
			((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_ALT_OD))
			temp |= 1 << pin;
		device->OTYPER = temp;
	}

	// Configura el registre PUPDR (Pull Up/Down Register)
	//
	if ((options & HAL_GPIO_MODE_mask) != HAL_GPIO_MODE_ANALOG) {
		temp = device->PUPDR;
		temp &= ~(0b11 << (pin * 2u));
		switch (options & HAL_GPIO_PULL_mask) {
			case HAL_GPIO_PULL_UP:
				temp |= 0b01 << (pin * 2);
				break;

			case HAL_GPIO_PULL_DOWN:
				temp |= 0b10 << (pin * 2);
				break;
		}
		device->PUPDR = temp;
	}

	// Configura el valor inicial pin de sortida
	//
	if (((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_PP) ||
		((options & HAL_GPIO_MODE_mask) == HAL_GPIO_MODE_OUTPUT_OD)) {

		temp = device->BSRR;
		if ((options & HAL_GPIO_INIT_mask) == HAL_GPIO_INIT_SET)
			temp |= 1 << pin;
		else
			temp |= 1 << (pin + 16);
		device->BSRR = temp;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Initialize a pin list.
/// \param    info: Settings table.
/// \param    count: Number of elements in table.
///
void halGPIOInitializePins(
	const GPIOPinSettings *settings,
	uint32_t count) {

	eosAssert(settings != NULL);
	eosAssert(count != 0);

	for (uint32_t i = 0; i < count; i++) {

		const GPIOPinSettings *p = &settings[i];
		GPIO_TypeDef* device = getDevice(p->port);

		enableDeviceClock(device);
		setupDevicePin(device, p->pin, p->options, p->alt);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Initialize a port list.
/// \param    info: Setup table.
/// \param    count: Number of elements in table.
///
void halGPIOInitializePorts(
	const GPIOPortSettings *settings,
	uint32_t count) {

	eosAssert(settings != NULL);
	eosAssert(count != 0);

	for (uint32_t i = 0; i < count; i++) {

		const GPIOPortSettings* p = &settings[i];
		GPIO_TypeDef* device = getDevice(p->port);

		enableDeviceClock(device);

		for (GPIOPin pin = 0; pin < 16; pin++)
			if (p->mask & (1 << pin))
				setupDevicePin(device, pin, p->options, p->alt);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Initialize a single pin.
/// \param    port: Port identifier.
/// \param    pin: Pin number
/// \param    options: Pin oOptions
/// \param    alt: Pin alternate function.
///
void halGPIOInitializePin(
	GPIOPort port,
	GPIOPin pin,
	GPIOOptions options,
	GPIOAlt alt) {

	__VERIFY_PORT(port);
	__VERIFY_PIN(pin);

	GPIO_TypeDef* device = getDevice(port);
	enableDeviceClock(device);

	setupDevicePin(device, pin, options, alt);
}


/// ----------------------------------------------------------------------
/// \brief    Let pin in clear state.
/// \param    port: Port identifier.
/// \param    pin: Pin number.
///
#if HAL_GPIO_INLINE == 0
inline void halGPIOClearPin(
	GPIOPort port,
	GPIOPin pin) {

	__VERIFY_PORT(port);
	__VERIFY_PIN(pin);

	GPIO_TypeDef* device = getDevice(port);
	device->BSRR = 1u << (pin + 16);

}
#endif


/// ----------------------------------------------------------------------
/// \brief    Let pin in set state.
/// \param    port: Port identifier.
/// \param    pin: Pin number.
///
#if HAL_GPIO_INLINE == 0
inline void halGPIOSetPin(
	GPIOPort port,
	GPIOPin pin) {

	__VERIFY_PORT(port);
	__VERIFY_PIN(pin);

	GPIO_TypeDef* device = getDevice(port);
	device->BSRR = 1u << pin;
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Toggle pin state.
/// \param    port: Port identifier.
/// \param    pin: Pin number.
///
#if HAL_GPIO_INLINE == 0
inline void halGPIOTogglePin(
	GPIOPort port,
	GPIOPin pin) {

	__VERIFY_PORT(port);
	__VERIFY_PIN(pin);

	GPIO_TypeDef* device = getDevice(p->port);
	device->ODR ^= 1u << pin;
}
#endif
