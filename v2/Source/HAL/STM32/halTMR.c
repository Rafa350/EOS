#include "hal/halTMR.h"
#if defined(STM32F4)
	#include "stm32f4xx_hal.h"
#elif defined(STM32F7)
	#include "stm32f7xx_hal.h"
#else
	#error Hardware no soportado
#endif


typedef struct {
	TIM_HandleTypeDef handle;
	TMRInterruptCallback pIrqCall;
	void *pIrqParams;
} TimerInfo;

static TimerInfo timerInfoTbl[HAL_TMR_TIMER_MAX];


/// ----------------------------------------------------------------------
/// \brief Activa el rellotge del temporitzador
/// \param timer: Identificador del temporitzador.
///
static void EnableTimerClock(
	TMRTimer timer) {

	switch (timer) {
		case HAL_TMR_TIMER_1:
			__HAL_RCC_TIM1_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_2:
			__HAL_RCC_TIM2_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_3:
			__HAL_RCC_TIM3_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_4:
			__HAL_RCC_TIM4_CLK_ENABLE();
			break;

		case HAL_TMR_TIMER_5:
			__HAL_RCC_TIM5_CLK_ENABLE();
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
static void DisableTimerClock(
	TMRTimer timer) {

	switch (timer) {
		case HAL_TMR_TIMER_1:
			__HAL_RCC_TIM1_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_2:
			__HAL_RCC_TIM2_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_3:
			__HAL_RCC_TIM3_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_4:
			__HAL_RCC_TIM4_CLK_DISABLE();
			break;

		case HAL_TMR_TIMER_5:
			__HAL_RCC_TIM5_CLK_DISABLE();
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
static void PrepareTimerHandle(
	TIM_HandleTypeDef *pHandle,
	const TMRInitializeInfo *pInfo) {

	static TIM_TypeDef * const instances[] = {
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

	static const uint32_t clockDivision[] = {
        TIM_CLOCKDIVISION_DIV1,
        TIM_CLOCKDIVISION_DIV2,
        TIM_CLOCKDIVISION_DIV4
	};

	pHandle->Instance = instances[pInfo->timer];
	pHandle->Init.CounterMode = TIM_COUNTERMODE_UP;
	pHandle->Init.ClockDivision = clockDivision[(pInfo->options & HAL_TMR_CLKDIV_MASK) >> HAL_TMR_CLKDIV_POS];
	pHandle->Init.Prescaler = pInfo->prescaler;
	pHandle->Init.Period = pInfo->period;
	pHandle->Init.RepetitionCounter = 0;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza un temporitzador
/// \param pInfo: Parametres d'inicialitzacio.
///
void halTMRInitialize(
	const TMRInitializeInfo *pInfo) {

	TMRTimer timer = pInfo->timer;
	TimerInfo *pTimerInfo = &timerInfoTbl[timer];

	EnableTimerClock(timer);

	PrepareTimerHandle(&pTimerInfo->handle, pInfo);
	HAL_TIM_Base_Init(&pTimerInfo->handle);

	if ((pInfo->options & HAL_TMR_INTERRUPT_MASK) == HAL_TMR_INTERRUPT_ENABLE) {

		static const IRQn_Type irq[] = {
			0,
		    TIM2_IRQn,
			TIM3_IRQn
		};

		pTimerInfo->pIrqCall = pInfo->pIrqCall;
		pTimerInfo->pIrqParams = pInfo->pIrqParams;

		HAL_NVIC_SetPriority(irq[timer], pInfo->irqPriority, pInfo->irqSubPriority);
		HAL_NVIC_EnableIRQ(irq[timer]);
	}
	else
		pTimerInfo->pIrqCall = NULL;
}


/// ----------------------------------------------------------------------
/// \brief Desactiva un temporitzador
/// \param id: Identificador del temporitzador.
///
void halTMRShutdown(
	TMRTimer timer) {

	TimerInfo *pTimerInfo = &timerInfoTbl[timer];

	HAL_TIM_Base_DeInit(&pTimerInfo->handle);

	DisableTimerClock(timer);
}


/// ----------------------------------------------------------------------
/// \brief Posa en marxa el temporitzador i comença a contar.
/// \param timer: El identificador del temporitzador.
///
void halTMRStartTimer(
	TMRTimer timer) {

	TimerInfo *pTimerInfo = &timerInfoTbl[timer];

	if (pTimerInfo->pIrqCall != NULL)
		__HAL_TIM_ENABLE_IT(&pTimerInfo->handle, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(&pTimerInfo->handle);
}


/// ----------------------------------------------------------------------
/// \brief Para el temporitzador.
/// \param timer: El identificador del temporitzador.
///
void halTMRStopTimer(
	TMRTimer timer) {

	TimerInfo *pTimerInfo = &timerInfoTbl[timer];

	if (pTimerInfo->pIrqCall != NULL)
		__HAL_TIM_DISABLE_IT(&pTimerInfo->handle, TIM_IT_UPDATE);
	__HAL_TIM_DISABLE(&pTimerInfo->handle);
}


/// ----------------------------------------------------------------------
/// \brief Retard en milisegons.
/// \param time: Temps en milisegons.
///
void halTMRDelay(
    uint32_t time) {

	HAL_Delay(time);
}


/// ----------------------------------------------------------------------
/// \brief Handler de la interrupcio.
/// \param timer: Identificador del temporitzador.
///
static void IRQHandler(
	TMRTimer timer) {

	TimerInfo *pTimerInfo = &timerInfoTbl[timer];

	if(__HAL_TIM_GET_FLAG(&pTimerInfo->handle, TIM_FLAG_UPDATE) != RESET) {
	    if(__HAL_TIM_GET_IT_SOURCE(&pTimerInfo->handle, TIM_IT_UPDATE) != RESET) {

	    	__HAL_TIM_CLEAR_IT(&pTimerInfo->handle, TIM_IT_UPDATE);

	      if (pTimerInfo->pIrqCall != NULL)
	    	  pTimerInfo->pIrqCall(timer, pTimerInfo->pIrqParams);
	    }
	}
}


/// ----------------------------------------------------------------------
/// \brief Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_2
void TIM2_IRQHandler() {

	IRQHandler(HAL_TMR_TIMER_2);
}
#endif


/// ----------------------------------------------------------------------
/// \brief Handler de la interrupcio.
///
#ifdef HAL_TMR_TIMER_3
void TIM3_IRQHandler() {

	IRQHandler(HAL_TMR_TIMER_3);
}
#endif

