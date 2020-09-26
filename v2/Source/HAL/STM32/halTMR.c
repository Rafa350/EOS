#include "eos.h"
#include "eosAssert.h"
#include "HAL/STM32/halTMR.h"
#include "HAL/STM32/halINT.h"

// TODO
// Eliminar les referencies a la llibreria HAL


typedef struct {
	TIM_HandleTypeDef handle;
	TMRInterruptFunction isrFunction;
	void* isrParams;
} TMRInfo;

static TMRInfo tmrInfoTbl[HAL_TMR_TIMER_MAX];

static const INTSource irq[] = {
	HAL_INT_SOURCE_TMR1_UP,
	HAL_INT_SOURCE_TMR2,
	HAL_INT_SOURCE_TMR3,
	HAL_INT_SOURCE_TMR4,
	HAL_INT_SOURCE_TMR5,
	HAL_INT_SOURCE_TMR6,
	HAL_INT_SOURCE_TMR7,
	HAL_INT_SOURCE_TMR8_UP
};


TMRRegisters* const tmrRegistersTbl[] = {
	TIM1,
	TIM2,
	TIM3,
	TIM4,
	TIM5,
	TIM6,
	TIM7,
	TIM8,
	TIM9,
	TIM10,
	TIM11,
	TIM12,
	TIM13,
	TIM14
};

/// ----------------------------------------------------------------------
/// \brief Activa el rellotge del temporitzador
/// \param[in] timer: Identificador del temporitzador.
///
static void enableClock(
	TMRTimer timer) {

	switch (timer) {
		case HAL_TMR_TIMER_1:
            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			break;

		case HAL_TMR_TIMER_2:
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			break;

		case HAL_TMR_TIMER_3:
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			break;

		case HAL_TMR_TIMER_4:
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			break;

		case HAL_TMR_TIMER_5:
            RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
			break;

#ifdef HAL_TMR_TIMER_6
		case HAL_TMR_TIMER_6:
			__HAL_RCC_TIM6_CLK_ENABLE();
			break;
#endif

		case HAL_TMR_TIMER_7:
			__HAL_RCC_TIM7_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_8:
			__HAL_RCC_TIM8_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_9:
			__HAL_RCC_TIM9_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_10:
			__HAL_RCC_TIM10_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_11:
			__HAL_RCC_TIM11_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_12:
			__HAL_RCC_TIM12_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_13:
			__HAL_RCC_TIM13_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_14:
			__HAL_RCC_TIM14_CLK_ENABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Desactiva el rellotge del temporitzador
/// \param timer: Identificador del temporitzador.
///
static void disableClock(
	TMRTimer timer) {

	switch (timer) {
		case HAL_TMR_TIMER_1:
            RCC->APB2ENR &= ~(RCC_APB2ENR_TIM1EN);
			break;

		case HAL_TMR_TIMER_2:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN);
			break;

		case HAL_TMR_TIMER_3:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN);
			break;

		case HAL_TMR_TIMER_4:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN);
			break;

		case HAL_TMR_TIMER_5:
			RCC->APB1ENR &= ~(RCC_APB1ENR_TIM5EN);
			break;

#ifdef HAL_TMR_TIMER_6
		case HAL_TMR_TIMER_6:
			__HAL_RCC_TIM6_CLK_DISABLE();
			break;
#endif

		case HAL_TMR_TIMER_7:
			__HAL_RCC_TIM7_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_8:
			__HAL_RCC_TIM8_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_9:
			__HAL_RCC_TIM9_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_10:
			__HAL_RCC_TIM10_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_11:
			__HAL_RCC_TIM11_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_12:
			__HAL_RCC_TIM12_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_13:
			__HAL_RCC_TIM13_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_14:
			__HAL_RCC_TIM14_CLK_DISABLE();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Prepara el handle per inicialitzar.
/// \brief pHandle: El handle a inicialitzar.
/// \param pInfo: Parametres d'inicialitzacio.
///
static void prepareTimerHandle(
	TIM_HandleTypeDef* handle,
	const TMRInitializeInfo* info) {

	static const uint32_t clockDivision[] = {
        TIM_CLOCKDIVISION_DIV1,
        TIM_CLOCKDIVISION_DIV2,
        TIM_CLOCKDIVISION_DIV4
	};

	handle->Instance = tmrRegistersTbl[info->timer];
	handle->Init.CounterMode = TIM_COUNTERMODE_UP;
	handle->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	handle->Init.ClockDivision = clockDivision[(info->options & HAL_TMR_CLKDIV_mask) >> HAL_TMR_CLKDIV_pos];
	handle->Init.Prescaler = info->prescaler;
	handle->Init.Period = info->period;
	handle->Init.RepetitionCounter = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Invoca a la funcio ISR.
/// \param    timer: El temporitzador.
///
static void invokeIsrFunction(
	TMRTimer timer) {

	TMRInfo* tmrInfo = &tmrInfoTbl[timer];
	if (tmrInfo->isrFunction != NULL)
		tmrInfo->isrFunction(timer, tmrInfo->isrParams);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza un temporitzador
/// \param    pInfo: Parametres d'inicialitzacio.
///
void halTMRInitialize(
	const TMRInitializeInfo* info) {

	// Precondicions
	//
	eosAssert(info != NULL);

	TMRTimer timer = info->timer;
	TMRInfo* tmrInfo = &tmrInfoTbl[timer];

	enableClock(timer);

	prepareTimerHandle(&tmrInfo->handle, info);
	HAL_TIM_Base_Init(&tmrInfo->handle);

	if ((info->options & HAL_TMR_INTERRUPT_mask) == HAL_TMR_INTERRUPT_ENABLE) {

		tmrInfo->isrFunction = info->isrFunction;
		tmrInfo->isrParams = info->isrParams;

		halTMREnableInterrupt(timer);
		halINTSetPriority(irq[timer], info->irqPriority, info->irqSubPriority);
		halINTEnableInterrupt(irq[timer]);
	}
	else
		tmrInfo->isrFunction = NULL;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva un temporitzador
/// \param    id: Identificador del temporitzador.
///
void halTMRShutdown(
	TMRTimer timer) {

	halTMRDisableInterrupt(timer);

	TMRInfo* tmrInfo = &tmrInfoTbl[timer];
	tmrInfo->isrFunction = NULL;
	HAL_TIM_Base_DeInit(&tmrInfo->handle);

	disableClock(timer);
}


/// ----------------------------------------------------------------------
/// \brief    Posa en marxa el temporitzador i comença a contar.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStartTimer(
	TMRTimer timer) {

	TMRRegisters* tmr = halTMRGetRegisterPtr(timer);
	tmr->CR1 |= TIM_CR1_CEN;
}


/// ----------------------------------------------------------------------
/// \brief    Para el temporitzador.
/// \param    timer: El identificador del temporitzador.
///
void halTMRStopTimer(
	TMRTimer timer) {

	TMRRegisters* tmr = halTMRGetRegisterPtr(timer);
	tmr->CR1 &= ~TIM_CR1_CEN;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la funcio d'interrupcio
/// \param    timer: El temporitzador.
/// \param    function: La funcio.
/// \param    params: El parametre de la funcioo.
///
void halTMRSetInterruptFunction(
	TMRTimer timer,
	TMRInterruptFunction function,
	void* params) {

	TMRInfo* tmrInfo = &tmrInfoTbl[timer];
	tmrInfo->isrFunction = function;
	tmrInfo->isrParams = params;
}


/// ----------------------------------------------------------------------
/// \brief    Activa les interrupcions del temporitzador.
/// \param    timer: El temporitzador.
///
void halTMREnableInterrupt(
	TMRTimer timer) {

	TMRRegisters* tmr = halTMRGetRegisterPtr(timer);

	// Permet al temporitzador generar interrupcions
	//
	tmr->DIER |= TIM_DIER_UIE;

	// Permet a la cpu acceptar interrupcions del temporitzador
	//
	halINTEnableInterrupt(irq[timer]);
}


/// ----------------------------------------------------------------------
/// \brief    Activa les interrupcions del temporitzador.
/// \param    timer: El temporitzador.
///
bool halTMRDisableInterrupt(
	TMRTimer timer) {

	TMRRegisters* tmr = halTMRGetRegisterPtr(timer);

	// Obte el valor previ.
	//
	bool enabled = (tmr->DIER & TIM_DIER_UIE) == TIM_DIER_UIE;

	// Impidex que el temporitzador generi interrupcions.
	//
	tmr->DIER &= ~TIM_DIER_UIE;

	// Evita que la cpu accepti interrupcions del temporitzador.
	//
	halINTDisableInterrupt(irq[timer]);

	return enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la prioritat de la interrupcio.
/// \param    timer: El temporitzador.
/// \param    priority: La prioritat
/// \param    subPriority: La sub-prioritat.
//
void halTMRSetInterruptPriority(
	TMRTimer timer,
	uint32_t priority,
	uint32_t subPriority) {

	halINTSetPriority(irq[timer], priority, subPriority);
}


/// ----------------------------------------------------------------------
/// \brief    Borra el indicador d'interrupcio del temporitzador.
/// \param    timer: Identificador del temporitzador.
/// \return   Valor del indicador.
///
void halTMRClearInterruptFlag(
	TMRTimer timer) {

	TMRRegisters* tmr = halTMRGetRegisterPtr(timer);
	tmr->SR &= ~TIM_SR_UIF;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del inficador d'interrupcio del temporitzador.
/// \param    timer: Identificador del temporitzador.
/// \return   El valor del indicador.
///
bool halTMRGetInterruptFlag(
	TMRTimer timer) {

	TMRRegisters* tmr = halTMRGetRegisterPtr(timer);
	return (tmr->SR & TIM_SR_UIF) == TIM_SR_UIF;
}


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
/// \param    timer: Identificador del temporitzador.
///
void halTIMInterruptHandler(
	TMRTimer timer) {

	TMRRegisters* tmr = halTMRGetRegisterPtr(timer);

	// Comprova si es un event UPDATE
	//
	if ((tmr->SR & TIM_SR_UIF) == TIM_SR_UIF) {
		tmr->SR &= ~TIM_SR_UIF;
		invokeIsrFunction(timer);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Retard en milisegons.
/// \param    time: Temps en milisegons.
///
void halTMRDelay(
    int time) {

	HAL_Delay(time);
}


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_2
void TIM2_IRQHandler() {

	halTIMInterruptHandler(HAL_TMR_TIMER_2);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_3
void TIM3_IRQHandler() {

	halTIMInterruptHandler(HAL_TMR_TIMER_3);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_4
void TIM4_IRQHandler() {

	halTIMInterruptHandler(HAL_TMR_TIMER_4);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_5
void TIM5_IRQHandler() {

	halTIMInterruptHandler(HAL_TMR_TIMER_5);
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_7
void TIM7_IRQHandler() {

	halTIMInterruptHandler(HAL_TMR_TIMER_7);
}
#endif

