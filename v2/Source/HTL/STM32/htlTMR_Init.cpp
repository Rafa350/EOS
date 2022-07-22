#include "eos.h"
#include "HTL/STM32/htlTMR.h"


using namespace htl;


static void enableClock(
	TIM_TypeDef *regs) {

	switch ((uint32_t) regs) {
		case TIM1_BASE:
            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			break;

		case TIM2_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			break;

		case TIM3_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			break;

		case TIM4_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			break;

		case TIM5_BASE:
            RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
			break;

		case TIM6_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
			break;

		case TIM7_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
			break;

		case TIM8_BASE:
			RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
			break;

		case TIM9_BASE:
			RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
			break;

		case TIM10_BASE:
			RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
			break;

		case TIM11_BASE:
			RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
			break;

		case TIM12_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
			break;

		case TIM13_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
			break;

		case TIM14_BASE:
			RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
			break;
	}

	__DSB();
}


static void disableClock(
	TIM_TypeDef *regs) {

	switch ((uint32_t) regs) {
		case TIM1_BASE:
            RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
			break;

		case TIM2_BASE:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;
			break;

		case TIM3_BASE:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;
			break;

		case TIM4_BASE:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;
			break;

		case TIM5_BASE:
            RCC->APB1ENR &= ~RCC_APB1ENR_TIM5EN;
			break;

		case TIM6_BASE:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;
			break;

		case TIM7_BASE:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM7EN;
			break;

		case TIM8_BASE:
			RCC->APB2ENR &= ~RCC_APB2ENR_TIM8EN;
			break;

		case TIM9_BASE:
			RCC->APB2ENR &= ~RCC_APB2ENR_TIM9EN;
			break;

		case TIM10_BASE:
			RCC->APB2ENR &= ~RCC_APB2ENR_TIM10EN;
			break;

		case TIM11_BASE:
			RCC->APB2ENR &= ~RCC_APB2ENR_TIM11EN;
			break;

		case TIM12_BASE:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM12EN;
			break;

		case TIM13_BASE:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM13EN;
			break;

		case TIM14_BASE:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM14EN;
			break;
	}
}


void htl::TMR_init(
	TIM_TypeDef *regs) {

	enableClock(regs);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza un temporitzador.
/// \param    regs: El bloc de registres.
///
void htl::TMR_deInit(
	TIM_TypeDef *regs) {

	// Para el timer
	//
	regs->CR1 &= ~TIM_CR1_CEN;

	// Desactiva les interrupcions
	//
	regs->DIER &= ~(TIM_DIER_UIE | TIM_DIER_TIE | TIM_DIER_COMIE);

	// Desactiva el clock del timer.
	//
	disableClock(regs);
}


