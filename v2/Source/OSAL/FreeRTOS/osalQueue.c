#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalQueue.h"
#include "FreeRTOS.h"
#include "queue.h"


/// ----------------------------------------------------------------------
/// \brief    Crea una cua.
/// \param    info: Parametres d'inicialitzacio.
/// \result   El handler de la cua. NULL en cas d'error.
///
HQueue osalQueueCreate(
	unsigned maxElements,
	unsigned elementSize) {

	eosAssert(maxElements > 0);
	eosAssert(elementSize > 0);

	HQueue hQueue = (HQueue) xQueueCreate(maxElements, elementSize);
	eosAssert(hQueue != NULL);

    return hQueue;
}


/// ----------------------------------------------------------------------
/// \brief    Destrueix una cua.
/// \param    hQueue: Handler de la cua.
///
void osalQueueDestroy(
	HQueue hQueue) {

	eosAssert(hQueue != NULL);

	vQueueDelete((QueueHandle_t) hQueue);
}


/// ----------------------------------------------------------------------
/// \brief    Buida el contingut de la cua.
/// \param    hQueue: Handler de la cua.
///
void osalQueueClear(
	HQueue hQueue) {

	eosAssert(hQueue != NULL);

	xQueueReset((QueueHandle_t) hQueue);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un element a la cua.
/// \param    hQueue: Handler de la cua.
/// \param    element: El element a afeigir.
/// \param    blockTime: Temps maxim de bloqueig en ms.
/// \return   True si tot es correcte.
///
bool osalQueuePut(
	HQueue hQueue,
	const void *element,
	unsigned blockTime) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    TickType_t blockTicks = (blockTime == ((unsigned) -1)) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;

    bool result;
    if (__is_isr_code()) {
        BaseType_t taskWoken = pdFALSE;
        result = xQueueSendFromISR((QueueHandle_t) hQueue, element, &taskWoken) == pdPASS;
        portEND_SWITCHING_ISR(taskWoken);
    }
    else
    	result = xQueueSendToBack((QueueHandle_t) hQueue, element,  blockTicks) == pdPASS;
    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un element a la cua. Aquesta versio es per ser
///           cridada d'ins d'una interrupcio.
/// \param    hQueue: Handler de la cua.
/// \param    element: El element a afeigir.
/// \return   True si tot es correcte
///
bool osalQueuePutISR(
	HQueue hQueue,
	const void *element) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    BaseType_t taskWoken = pdFALSE;
    bool result = xQueueSendFromISR((QueueHandle_t) hQueue, element, &taskWoken) == pdPASS;
    portEND_SWITCHING_ISR(taskWoken);
    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua.
/// \param    hQueue: Handler de la cua.
/// \param    element: Buffer on deixar l'element.
/// \param    blockTime: Temps maxim de bloqueig en ms.
/// \return   True si tot es correcte
///
bool osalQueueGet(
	HQueue hQueue,
	void *element,
	unsigned blockTime) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    TickType_t blockTicks = (blockTime == ((unsigned)-1)) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;

    bool result;
    if (__is_isr_code()) {
        BaseType_t taskWoken = pdFALSE;
        result = xQueueReceiveFromISR((QueueHandle_t)hQueue, element, &taskWoken) == pdPASS;
        portEND_SWITCHING_ISR(taskWoken);
    }
    else
    	result = xQueueReceive((QueueHandle_t)hQueue, element, blockTicks) == pdPASS;
    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua. Aquesta versio es per ser cridada
///           d'ins d'una interrupcio.
/// \param    hQueue: Handler de la cua.
/// \param    element: Buffer on deixar l'element.
/// \return   True si tot es correcte.
///
bool osalQueueGetISR(
	HQueue hQueue,
	void *element) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    BaseType_t taskWoken = pdFALSE;
    bool result = xQueueReceiveFromISR((QueueHandle_t) hQueue, element, &taskWoken) == pdPASS;
    portEND_SWITCHING_ISR(taskWoken);
    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la cua es buida.
/// \param    hQueue: Handler de la cua.
/// \return   TRue si es buida, false en cas contrari.
///
bool osalQueueIsEmpty(
	HQueue hQueue) {

	eosAssert(hQueue != NULL);

	return uxQueueMessagesWaiting((QueueHandle_t) hQueue) == 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la cua es buida d'ins d'una interrupcio.
/// \param    hQueue: Handler de la cua.
/// \return   TRue si es buida, false en cas contrari.
///
bool osalQueueIsEmptyISR(
	HQueue hQueue) {

	eosAssert(hQueue != NULL);

	return uxQueueMessagesWaitingFromISR((QueueHandle_t) hQueue) == 0;
}
