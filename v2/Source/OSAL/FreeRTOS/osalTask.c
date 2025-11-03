#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalTask.h"

#include "FreeRTOS.h"
#include "task.h"


#if configNUM_THREAD_LOCAL_STORAGE_POINTERS < 1
#error "configNUM_THREAD_LOCAL_STORAGE_POINTERS ha de ser mayor que 0"
#endif


#define TAG_INDEX_DATA 0


/// ----------------------------------------------------------------------
/// \brief    Crea una tasca.
/// \param    info: Parametres d'inicialitzacio.
/// \return   El handler de la tasca. NULL en cas d'error.
///
HTask osalTaskCreate(
	const TaskInitializeInfo* info) {

    eosAssert(info != NULL);

	// Crea la tasca.
	//
	HTask hTask;
    if (xTaskCreate(
        (TaskFunction_t) info->function,
        (const portCHAR*) info->name == NULL ? "" : info->name,
        info->stackSize,
        info->params,
        tskIDLE_PRIORITY + ((UBaseType_t) (info->options & OSAL_TASK_PRIORITY_mask) >> OSAL_TASK_PRIORITY_pos),
        (TaskHandle_t*) &hTask) != pdPASS)
		return NULL;

    vTaskSetThreadLocalStoragePointer((TaskHandle_t) hTask, TAG_INDEX_DATA, info->ptrData);

   	return hTask;
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix la tasca.
/// \param    hTask: El handler de la tasca. NULL si es la tasca actual.
///
void osalTaskDestroy(
	HTask hTask) {

	vTaskDelete((TaskHandle_t) hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Suspend l'execucio de la tasca.
/// \param    hTask: El handler de la tasca.
///
void osalTaskSuspend(
	HTask hTask) {

	vTaskSuspend((TaskHandle_t) hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Resumeix l'execucio de la tasca.
/// \param    hTask: El handler de la tasca.
///
void osalTaskResume(
	HTask hTask) {

	vTaskResume((TaskHandle_t) hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Canvia la prioritat de la tasca.
/// \param    hTask: El handler de la tasca. NULL si es la tasca actual.
/// \param    priority: La prioritat.
///
void osalTaskSetPriority(
    HTask hTask,
    uint8_t priority) {

    vTaskPrioritySet(
        (TaskHandle_t) hTask,
        tskIDLE_PRIORITY + ((UBaseType_t) (priority & OSAL_TASK_PRIORITY_mask) >> OSAL_TASK_PRIORITY_pos));
}


/// ----------------------------------------------------------------------
/// \brief    Pasa el control a un altre tasca.
///
void osalTaskYield(void) {

	taskYIELD();
}


/// ----------------------------------------------------------------------
/// \brief    Retorna la marca de nivell de la pila.
/// \return   El resultat.
///
unsigned osalTaskGetStackHighWaterMark(void) {

	return uxTaskGetStackHighWaterMark(NULL);
}


/// ----------------------------------------------------------------------
/// \brief    Espera una notificacio directa.
/// \param    clear: Borrat de contadors.
/// \param    waitTime: Temps d'espera.
///
bool osalTaskWaitNotification(
	bool clear,
	unsigned waitTime) {

    auto waitTicks = (waitTime == ((unsigned) -1)) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
	return ulTaskNotifyTake(clear ? pdTRUE : pdFALSE, waitTicks);
}


/// ----------------------------------------------------------------------
/// \brief    Envia una notificacio directe a la tasca.
/// \param    hTask: Hander de la tasca.
///
void osalTaskRaiseNotification(
	HTask hTask) {

	xTaskNotifyGive((TaskHandle_t) hTask);
}


/// ----------------------------------------------------------------------
/// \brief    Envia una notificacio directe a la tasca, desde dins
///           d'una interrupcio.
/// \param    hTask: Hander de la tasca.
///
void osalTaskRaiseNotificationISR(
	HTask hTask) {

	portBASE_TYPE taskWoken = pdFALSE;

	vTaskNotifyGiveFromISR((TaskHandle_t) hTask, &taskWoken);
	portYIELD_FROM_ISR(taskWoken);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el punter a les dades de la tasca.
/// \param    hTask: El handler de la tasca.
/// \param    El punter.
///
void* osalGetPtrData(
	HTask hTask) {

	return pvTaskGetThreadLocalStoragePointer((TaskHandle_t)hTask, TAG_INDEX_DATA);
}


/// ----------------------------------------------------------------------
/// \brief    Obte el handler de la tasca en execucio.
/// \return   El handler.
///
HTask osalGetCurrentTask(void) {

	return (HTask) xTaskGetCurrentTaskHandle();
}
