#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halEXTI.h"


void halEXTIInitialize(
	EXTILine line,
	EXTIOptions options) {

/*

	// Activa el modul SYSCFG
	//
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

		// Configura el registre EXTICR
		//
        temp = SYSCFG->EXTICR[pin >> 2];
        temp &= ~(((uint32_t)0x0F) << (4 * (pin & 0x03)));
        temp |= ((uint32_t)(port) << (4 * (pin & 0x03)));
        SYSCFG->EXTICR[pin >> 2] = temp;

		// Configura el registre IMR (Interrupt Mask Register);
		//
		EXTI->IMR |= 1 << pin;

		// Configura el registre EMR (Event Mask Register);
		//
        //EXTI->EMR |= 1 << pin;

		// Configura el registre RTSR (Rising Trigger Selection Register)
		//
		if (((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_IT_POS) ||
			((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_IT_CHG))
			EXTI->RTSR |= 1 << pin;
		else
			EXTI->RTSR &= ~(1 << pin);

		// Configura el registre FTSR (Falling Trigger Selection Register)
		//
		if (((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_IT_NEG) ||
			((options & HAL_GPIO_MODE_MASK) == HAL_GPIO_MODE_IT_CHG))
			EXTI->FTSR |= 1 << pin;
		else
			EXTI->FTSR &= ~(1 << pin);
	}
	else {
		EXTI->IMR &= ~(1 << pin);
        EXTI->EMR &= ~(1 << pin);
		EXTI->RTSR &= ~(1 << pin);
		EXTI->FTSR &= ~(1 << pin);
	}*/
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI0
///
void EXTI0_IRQHandler(void) {

}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI1
///
void EXTI1_IRQHandler(void) {

}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI2
///
void EXTI2_IRQHandler(void) {

}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI3
///
void EXTI3_IRQHandler(void) {

}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio EXTI4
///
void EXTI4_IRQHandler(void) {

}

