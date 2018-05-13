#include "osal/osalThread.h"
#include "eosAssert.h"
#include "FreeRTOS.h"
#include "task.h"


static const char *defaultName = ""; // El nom de la tasca no pot ser NULL en FreeRTOS


/// ----------------------------------------------------------------------
/// \brief Crea una tasca.
/// \param info: Parametres d'inicialitzacio.
/// \param handler: El handler de la tasca.
/// \return El resultat de l'operacio.
///
uint8_t osalTaskCreate(
	const TaskInitializeInfo *info,
	TaskHandler *handler) {

#ifdef OSAL_CHACK_PARAMETERS
	if (info == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;

	if (handler == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

	uint32_t priority = info->options & OSAL_TASK_PRIORITY_MASK;

    xTaskCreate(
        info->function,
        info->name == NULL ? defaultName : info->name,
        info->stackSize,
        info->params,
        tskIDLE_PRIORITY + ((UBaseType_t) priority),
        handler);
    if (*handler == NULL)
    	return OSAL_STATUS_ERROR_RESOURCE;

    return OSAL_STATUS_OK;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix la tasca.
/// \param handler: El handler de la tasca.
///
uint8_t osalTaskDestroy(
	TaskHandler handler) {

#ifdef OSAL_CHACK_PARAMETERS
	if (handler == NULL)
		return OSAL_STATUS_ERROR_PARAMETER;
#endif

	vTaskDelete(handler);

	return OSAL_STATUS_OK;
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

	if (time > 0)
        vTaskDelay(time / portTICK_PERIOD_MS);
}


void osalDelayUntil(
	unsigned time,
	unsigned *lastTick) {

    if (time > 0)
        vTaskDelayUntil((TickType_t*) lastTick, time / portTICK_PERIOD_MS);
}
