#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalTask.h"

#include "FreeRTOS.h"
#include "task.h"


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


void osalTaskSuspend(
	HTask hTask) {

	vTaskSuspend((TaskHandle_t) hTask);
}


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
