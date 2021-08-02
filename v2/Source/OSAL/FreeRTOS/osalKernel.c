#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalKernel.h"

#include "FreeRTOS.h"
#include "task.h"


extern void xPortSysTickHandler(void);


/// ----------------------------------------------------------------------
/// \brief    Entra en una seccio critica.
///
void osalEnterCritical() {

    taskENTER_CRITICAL();
}


/// ----------------------------------------------------------------------
/// brief     Surt d'una seccio critica.
///
void osalExitCritical() {

    taskEXIT_CRITICAL();
}


/// ----------------------------------------------------------------------
/// \brief    Posa en marxa el planificador de tasques.
///
void osalStartScheduler() {

	vTaskStartScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Parada del planificador de tasques.
///
void osalStopScheduler() {

	vTaskEndScheduler();
}


/// ----------------------------------------------------------------------
/// \brief    Posa en pausa totes les tasques excepte l'actual.
///
void osalSuspendAll() {

    vTaskSuspendAll();
}


/// ----------------------------------------------------------------------
/// \brief    Resumeix les tasques que estan en pausa.
///
void osalResumeAll() {

	xTaskResumeAll();
}


/// ----------------------------------------------------------------------
/// \brief    Suspen l'execucio de la tasca actual, durant un periode de temps.
/// \param    time: Temps en ms.
///
void osalDelay(
	unsigned time) {

	unsigned ticks = time / portTICK_PERIOD_MS;
	if (ticks > 0)
		vTaskDelay(ticks);
}


void osalDelayUntil(
	unsigned time,
	unsigned* lastTick) {

	unsigned ticks = time / portTICK_PERIOD_MS;
    if (ticks > 0)
        vTaskDelayUntil((TickType_t*) lastTick, ticks);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del contador de ticks.
/// \retorn   El valor del contador.
///
unsigned osalGetTickCount() {

	return xTaskGetTickCount();
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor del contador de ticks en milisegons.
/// \retorn   El valor del contador.
///
unsigned osalGetTickTime() {

    return xTaskGetTickCount() * portTICK_PERIOD_MS;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el tick del sistema.
///
void osalSysTickHandler() {

#if (INCLUDE_xTaskGetSchedulerState == 1)
	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
#endif
		xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1)
	}
#endif
}

