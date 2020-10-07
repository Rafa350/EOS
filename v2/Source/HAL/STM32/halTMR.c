#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halTMR.h"


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el handler del temporitzador.
/// \param    data: Bloc de memoria pel handler del temporitzador.
/// \param    info: Parametres d'inicialitzacio.
/// \return   El handler del temporitzador.
///
TMRHandler halTMRInitialize(
	TMRData* data,
	const TMRInitializeInfo* info) {

	TMRHandler handler = data;

	switch (info->timer) {
		case HAL_TMR_TIMER_1:
            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			handler->regs = TIM1;
			break;

		case HAL_TMR_TIMER_2:
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			handler->regs = TIM2;
			break;

		case HAL_TMR_TIMER_3:
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			handler->regs = TIM3;
			break;

		case HAL_TMR_TIMER_4:
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			handler->regs = TIM4;
			break;

		case HAL_TMR_TIMER_5:
            RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
			handler->regs = TIM5;
			break;

		case HAL_TMR_TIMER_6:
			RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
			handler->regs = TIM6;
			break;

		case HAL_TMR_TIMER_7:
			RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
			handler->regs = TIM7;
			break;

		case HAL_TMR_TIMER_8:
			RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
			handler->regs = TIM8;
			break;

		case HAL_TMR_TIMER_9:
			RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
			handler->regs = TIM9;
			break;

		case HAL_TMR_TIMER_10:
			RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
			handler->regs = TIM10;
			break;

		case HAL_TMR_TIMER_11:
			RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
			handler->regs = TIM11;
			break;

		case HAL_TMR_TIMER_12:
			RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
			handler->regs = TIM12;
			break;

		case HAL_TMR_TIMER_13:
			RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
			handler->regs = TIM13;
			break;

		case HAL_TMR_TIMER_14:
			RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
			handler->regs = TIM14;
			break;
	}

	uint32_t temp;

	// Configura el registre CR1 (Control 1)
	//
	temp = handler->regs->CR1;
	temp &= ~(TIM_CR1_CEN);                 // Para el timer

	if (IS_TIM_CLOCK_DIVISION_INSTANCE(handler->regs)) {
		temp &= ~(TIM_CR1_CKD); 			// Divisor per 1 per defecte
		switch ((info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos) {
			case HAL_TMR_CLKDIV_2:
				temp |= TIM_CR1_CKD_0;      // Divisor per 2
				break;

			case HAL_TMR_CLKDIV_4:          // Divisor per 4
				temp |= TIM_CR1_CKD_1;
				break;
		}
	}

	if ((info->options & HAL_TMR_DIRECTION_mask) == HAL_TMR_DIRECTION_DOWN)
		temp |= TIM_CR1_DIR;                // Conta cap avall

	handler->regs->CR1 = temp;

	// Configura el registre PSC (Prescaler)
	//
	handler->regs->PSC = info->prescaler;

	// Configura el registre ARR (Periode)
	//
	handler->regs->ARR = info->period;

	// Configura la funcio ISR
	//
	handler->isrFunction = NULL;
	handler->isrParams = NULL;

	return handler;
}


/// ----------------------------------------------------------------------
/// \brief    Desactivacio del temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRShutdown(
	TMRHandler handler) {

	eosAssert(handler != NULL);

	halTMRStopTimer(handler);
	halTMRDisableInterrupts(handler, HAL_TMR_EVENT_ALL);

	switch ((uint32_t)handler->regs) {
		case TIM1_BASE:
            RCC->APB2ENR &= ~(RCC_APB2ENR_TIM1EN);
			break;

		case TIM2_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN);
			break;

		case TIM3_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN);
			break;

		case TIM4_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN);
			break;

		case TIM5_BASE:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM5EN);
			break;

		case TIM6_BASE:
			__HAL_RCC_TIM6_CLK_DISABLE();
			break;

		case TIM7_BASE:
			__HAL_RCC_TIM7_CLK_DISABLE();
			break;

		case TIM8_BASE:
			__HAL_RCC_TIM8_CLK_DISABLE();
			break;

		case TIM9_BASE:
			__HAL_RCC_TIM9_CLK_DISABLE();
			break;

		case TIM10_BASE:
			__HAL_RCC_TIM10_CLK_DISABLE();
			break;

		case TIM11_BASE:
			__HAL_RCC_TIM11_CLK_DISABLE();
			break;

		case TIM12_BASE:
			__HAL_RCC_TIM12_CLK_DISABLE();
			break;

		case TIM13_BASE:
			__HAL_RCC_TIM13_CLK_DISABLE();
			break;

		case TIM14_BASE:
			__HAL_RCC_TIM14_CLK_DISABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Activa el temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRStartTimer(
	TMRHandler handler) {

	eosAssert(handler != NULL);

	handler->regs->CR1 |= TIM_CR1_CEN;      // Activa el temporitzador.
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva el temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRStopTimer(
	TMRHandler handler) {

	eosAssert(handler != NULL);

	handler->regs->CR1 &= ~TIM_CR1_CEN;     // Desactiva el temporitzador
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la funcio de gestion de la interrupcio.
/// \param    handler: Handler del temporitzador.
/// \param    function: La funcio.
/// \param    params: El parametre.
///
void halTMRSetInterruptFunction(
	TMRHandler handler,
	TMRInterruptFunction function,
	void* params) {

	eosAssert(handler != NULL);

	handler->isrFunction = function;
	handler->isrParams = params;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa las interrupcions del temporitzador.
/// \param    handler: Handler del temporitzador.
///
void halTMRInterruptHandler(
	TMRHandler handler) {

	eosAssert(handler != NULL);

	// Comprova si es un event UPDATE
	//
	if ((handler->regs->SR & TIM_SR_UIF) == TIM_SR_UIF) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams);
		handler->regs->SR &= ~TIM_SR_UIF;
	}

	// Comprova si es un event TRIGGER
	//
	if ((handler->regs->SR & TIM_SR_TIF) == TIM_SR_TIF) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams);
		handler->regs->SR &= ~TIM_SR_TIF;
	}

	// Comprova si es un event COM
	//
	if ((handler->regs->SR & TIM_SR_COMIF) == TIM_SR_COMIF) {
		if (handler->isrFunction != NULL)
			handler->isrFunction(handler, handler->isrParams);
		handler->regs->SR &= ~TIM_SR_COMIF;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Activa les interrupcions del temporitzador.
/// \param    handler: Handler del temporitzador.
/// \param    events: Events a activar.
///
void halTMREnableInterrupts(
	TMRHandler handler,
	uint32_t events) {

	uint32_t temp = handler->regs->DIER;

	if ((events & HAL_TMR_EVENT_UP) == HAL_TMR_EVENT_UP)
		temp |= TIM_DIER_UIE;
	if ((events & HAL_TMR_EVENT_TRG) == HAL_TMR_EVENT_TRG)
		temp |= TIM_DIER_TIE;
	if ((events & HAL_TMR_EVENT_COM) == HAL_TMR_EVENT_COM)
		temp |= TIM_DIER_COMIE;

	handler->regs->DIER = temp;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva les interrupcions del temporitzador.
/// \param    handler: Handler del temporitzador.
/// \param    events: Events a desactivar.
/// \return   Els events previament actius.
///
uint32_t halTMRDisableInterrupts(
	TMRHandler handler,
	uint32_t events) {

	uint32_t temp = handler->regs->DIER;

	uint32_t enabled = 0;
	if ((temp & TIM_DIER_UIE) == TIM_DIER_UIE)
		enabled |= HAL_TMR_EVENT_UP;
	if ((temp & TIM_DIER_UIE) == TIM_DIER_TIE)
		enabled |= HAL_TMR_EVENT_TRG;
	if ((temp & TIM_DIER_UIE) == TIM_DIER_COMIE)
		enabled |= HAL_TMR_EVENT_COM;

	if ((events & HAL_TMR_EVENT_UP) == HAL_TMR_EVENT_UP)
		temp &= ~TIM_DIER_UIE;
	if ((events & HAL_TMR_EVENT_TRG) == HAL_TMR_EVENT_TRG)
		temp &= ~TIM_DIER_TIE;
	if ((events & HAL_TMR_EVENT_COM) == HAL_TMR_EVENT_COM)
		temp &= ~TIM_DIER_COMIE;

	handler->regs->DIER = temp;

	return enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Borra el indicador d'interrupcio del temporitzador.
/// \param    handler: Handler del temporitzador.
/// \return   Valor del indicador.
///
void halTMRClearInterruptFlags(
	TMRHandler handler,
	uint32_t events) {

	if ((events & HAL_TMR_EVENT_UP) == HAL_TMR_EVENT_UP)
		handler->regs->SR &= ~TIM_SR_UIF;

	if ((events & HAL_TMR_EVENT_TRG) == HAL_TMR_EVENT_TRG)
		handler->regs->SR &= ~TIM_SR_TIF;

	if ((events & HAL_TMR_EVENT_COM) == HAL_TMR_EVENT_COM)
		handler->regs->SR &= ~TIM_SR_COMIF;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del indicador d'interrupcio del temporitzador.
/// \param    handler: Handler del tempositzador.
/// \param    event: Identificador del event
/// \return   El valor del indicador.
///
bool halTMRGetInterruptFlag(
	TMRHandler handler,
	uint32_t event) {

	switch (event) {
		case HAL_TMR_EVENT_UP:
			return (handler->regs->SR & TIM_SR_UIF) == TIM_SR_UIF;

		case HAL_TMR_EVENT_TRG:
			return (handler->regs->SR & TIM_SR_TIF) == TIM_SR_TIF;

		case HAL_TMR_EVENT_COM:
			return (handler->regs->SR & TIM_SR_COMIF) == TIM_SR_COMIF;

		default:
			return false;
	}
}
