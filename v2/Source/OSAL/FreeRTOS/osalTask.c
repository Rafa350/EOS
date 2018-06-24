#include "osal/osalTask.h"
#include "eosAssert.h"
#include "FreeRTOS.h"
#include "task.h"


static const char *defaultName = ""; // El nom de la tasca no pot ser NULL en FreeRTOS


/// ----------------------------------------------------------------------
/// \brief Crea una tasca.
/// \param info: Parametres d'inicialitzacio.
/// \return El handler de la tasca. NULL en cas d'error.
///
HTask osalTaskCreate(
	const TaskInitializeInfo *info) {

	// Comprova que els parametres siguin correctes.
	//
	if (info == NULL)
		return NULL;

	// Crea la tasca.
	//
	HTask hTask;
    if (xTaskCreate(
        info->function,
        info->name == NULL ? defaultName : info->name,
        info->stackSize,
        info->params,
        tskIDLE_PRIORITY + ((UBaseType_t) (info->options & OSAL_TASK_PRIORITY_MASK)),
        (TaskHandle_t*) &hTask) != pdPASS)
		return NULL;

    // Tot correcte. Retorna el handler.
    //
    return hTask;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix la tasca.
/// \param hTask: El handler de la tasca. NULL si es la tasca actual.
///
void osalTaskDestroy(
	HTask hTask) {

	vTaskDelete(hTask);
}


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
/// \brief Obte el valor del contador de ticks.
/// \retorn El valor del contador.
///
unsigned osalGetTickCount() {

	return xTaskGetTickCount();
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
