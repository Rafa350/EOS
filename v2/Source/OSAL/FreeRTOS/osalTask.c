#include "eos.h"
#include "eosAssert.h"
#include "osal/osalTask.h"
#include "FreeRTOS.h"
#include "task.h"



/// ----------------------------------------------------------------------
/// \brief Crea una tasca.
/// \param info: Parametres d'inicialitzacio.
/// \return El handler de la tasca. NULL en cas d'error.
///
HTask osalTaskCreate(
	const TaskInitializeInfo *info) {

    eosAssert(info != NULL);

	// Crea la tasca.
	//
	HTask hTask;
    if (xTaskCreate(
        info->function,
        info->name == NULL ? "" : info->name,
        info->stackSize,
        info->params,
        tskIDLE_PRIORITY + ((UBaseType_t) (info->options & OSAL_TASK_PRIORITY_MASK)),
        (TaskHandle_t*) &hTask) != pdPASS)
		return NULL;

    return hTask;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix la tasca.
/// \param hTask: El handler de la tasca. NULL si es la tasca actual.
///
void osalTaskDestroy(
	HTask hTask) {

	eosAssert(hTask != NULL);

	vTaskDelete(hTask);
}


/// ----------------------------------------------------------------------
/// \brief Pasa el control a un altre tasca.
///
void osalTaskYield() {

	taskYIELD();
}
