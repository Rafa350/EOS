#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalTask.h"
#include "FreeRTOS.h"
#include "task.h"



/// ----------------------------------------------------------------------
/// \brief Crea una tasca.
/// \param[in] pInfo: Parametres d'inicialitzacio.
/// \return El handler de la tasca. NULL en cas d'error.
///
HTask osalTaskCreate(
	const TaskInitializeInfo *pInfo) {

    eosAssert(info != NULL);

	// Crea la tasca.
	//
	HTask hTask;
    if (xTaskCreate(
        pInfo->function,
        pInfo->name == NULL ? "" : info->name,
        pInfo->stackSize,
        pInfo->params,
        tskIDLE_PRIORITY + ((UBaseType_t) (pInfo->options & OSAL_TASK_PRIORITY_MASK)),
        (TaskHandle_t*) &hTask) != pdPASS)
		return NULL;

    return hTask;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix la tasca.
/// \param[in] hTask: El handler de la tasca. NULL si es la tasca actual.
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
