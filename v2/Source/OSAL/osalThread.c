#include "osal/osalThread.h"
#include "eosAssert.h"
#include "FreeRTOS.h"
#include "task.h"


static const char *defaultName = ""; // El nom de la tasca no pot der NULL en FreeRTOS


/// ----------------------------------------------------------------------
/// \brief Crea una tasca.
/// \param info: Parametres d'inicialitzacio.
/// \return El handler de la tasca. NULL en cas d'error
///
TaskHandler osalTaskCreate(
	const TaskInitializeInfo *info) {

	eosArgumentIsNotNull(info);

	TaskHandler handler;

	uint32_t priority = info->options & OSAL_TASK_PRIORITY_MASK;

    xTaskCreate(
        info->function,
        info->name == NULL ? defaultName : info->name,
        info->stackSize,
        info->params,
        tskIDLE_PRIORITY + ((UBaseType_t) priority),
        &handler);

    eosAssert(handler != NULL);

    return handler;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix la tasca.
/// \param handler: El handler de la tasca.
///
void osalTaskDestroy(
	TaskHandler handler) {

	eosArgumentIsNotNull(handler);

	vTaskDelete(handler);
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
void osalDelay(unsigned time) {

	if (time > 0)
        vTaskDelay(time / portTICK_PERIOD_MS);
}
