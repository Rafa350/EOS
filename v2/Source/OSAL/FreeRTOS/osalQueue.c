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
/// \param    waitTime: Temps d'espera ms.
/// \return   True si tot es correcte.
///
bool osalQueuePut(
	HQueue hQueue,
	const void *element,
	unsigned waitTime) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    unsigned waitTicks = (waitTime == ((unsigned) -1)) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
    return xQueueSendToBack((QueueHandle_t) hQueue, element,  waitTicks) == pdPASS;
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
    if (result)
    	portEND_SWITCHING_ISR(taskWoken);
    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua.
/// \param    hQueue: Handler de la cua.
/// \param    element: Buffer on deixar l'element.
/// \param    waitTime: Temps maxim de bloqueig en ms.
/// \return   True si tot es correcte
///
bool osalQueueGet(
	HQueue hQueue,
	void *element,
	unsigned waitTime) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    unsigned waitTicks = (waitTime == ((unsigned) -1)) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
    return xQueueReceive((QueueHandle_t)hQueue, element, waitTicks) == pdPASS;
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
    if (result)
    	portEND_SWITCHING_ISR(taskWoken);
    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua.
/// \param    hQueue: Handler de la cua.
/// \param    element: Buffer on deixar l'element.
/// \param    waitTime: Temps maxim de bloqueig en ms.
/// \return   True si tot es correcte
///
bool osalQueuePeek(
	HQueue hQueue,
	void *element,
	unsigned waitTime) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    TickType_t waitTicks = (waitTime == ((unsigned) -1)) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
    return xQueuePeek((QueueHandle_t)hQueue, element, waitTicks) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua. Aquesta versio es per ser cridada
///           d'ins d'una interrupcio.
/// \param    hQueue: Handler de la cua.
/// \param    element: Buffer on deixar l'element.
/// \return   True si tot es correcte.
///
bool osalQueuePeekISR(
	HQueue hQueue,
	void *element) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    bool result = xQueuePeekFromISR((QueueHandle_t) hQueue, element) == pdPASS;
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
