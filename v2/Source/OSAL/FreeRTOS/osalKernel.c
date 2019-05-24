#include "eos.h"
#include "eosAssert.h"
#include "osal/osalKernel.h"
#include "FreeRTOS.h"
#include "task.h"



/// ----------------------------------------------------------------------
/// \brief Entra en una seccio critica.
///
void osalEnterCritical() {

    taskENTER_CRITICAL();
}


/// ----------------------------------------------------------------------
/// brief Surt d'una seccio critica.
///
void osalExitCritical() {

    taskEXIT_CRITICAL();
}


/// ----------------------------------------------------------------------
/// \brief Posa en marxa el planificador de tasques.
///
void osalStartScheduler() {

	vTaskStartScheduler();
}


/// ----------------------------------------------------------------------
/// \brief Parada del planificador de tasques.
///
void osalStopScheduler() {

	vTaskEndScheduler();
}


/// ----------------------------------------------------------------------
/// \brief Posa en pausa totes les tasques excepte l'actual.
///
void osalSuspendAll() {

    vTaskSuspendAll();
}


/// ----------------------------------------------------------------------
/// \brief Resumeix les tasques que estan en pausa.
///
void osalResumeAll() {

	xTaskResumeAll();
}


/// ----------------------------------------------------------------------
/// \brief Suspen l'execucio de la tasca actual, durant un periode de temps.
/// \param time: Temps en ms.
///
void osalDelay(
	unsigned time) {

    vTaskDelay((time ? time : time + 1) / portTICK_PERIOD_MS);
}


void osalDelayUntil(
	unsigned time,
	unsigned *lastTick) {

    if (time > 0)
        vTaskDelayUntil((TickType_t*) lastTick, time / portTICK_PERIOD_MS);
}


/// ----------------------------------------------------------------------
/// \brief Obte el valor del contador de ticks.
/// \retorn El valor del contador.
///
unsigned osalGetTickCount() {

	return xTaskGetTickCount();
}


/// ----------------------------------------------------------------------
/// \brief Procesa el tick del sistema.
///
void osalSystickHandler() {

#if (INCLUDE_xTaskGetSchedulerState  == 1)
	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
#endif
		xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState  == 1)
	}
#endif
}

