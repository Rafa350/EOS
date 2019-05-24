#include "eos.h"
#include "eosAssert.h"
#include "osal/osalQueue.h"
#include "osal/osalMemory.h"
#include "FreeRTOS.h"
#include "queue.h"



/// ----------------------------------------------------------------------
/// \brief Crea una cua.
/// \param info: Parametres d'inicialitzacio.
/// \result El handler de la cua. NULL en cas d'error.
///
HQueue osalQueueCreate(
	const QueueInitializeInfo *info) {

	eosAssert(info != NULL);

	HQueue hQueue = xQueueCreate(info->maxElements, info->elementSize);
	eosAssert(hQueue != NULL);

    return hQueue;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix una cua.
/// \param hQueue: El handler de la cua.
///
void osalQueueDestroy(
	HQueue hQueue) {

	eosAssert(hQueue != NULL);

	vQueueDelete(hQueue);
}


/// ----------------------------------------------------------------------
/// \brief Buida el contingut de la cua.
/// \param hQueue: El handler de la cua.
///
void osalMsgQueueClear(
	HQueue hQueue) {

	eosAssert(hQueue != NULL);

	xQueueReset(hQueue);
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element a la cua.
/// \param hQueue: El handler de la cua.
/// \param element: El element a afeigir.
/// \param waitTime: Temps maxim de bloqueig en ms.
/// \return True si tot es correcte.
///
bool osalQueuePut(
	HQueue hQueue,
	const void *element,
	unsigned waitTime) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    TickType_t ticks = waitTime == ((unsigned) -1) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
    return xQueueSendToBack(hQueue, element,  ticks) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element a la cua. Aquesta versio es per ser cridada
///		   d'ins d'una interrupcio.
/// \param hQueue: El handler de la cua.
/// \param element: El element a afeigir.
/// \return True si tot es correcte
///
bool osalQueuePutISR(
	HQueue hQueue,
	const void *element) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    BaseType_t priority = pdFALSE;
    return xQueueSendFromISR(hQueue, element, &priority) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief Obte un element de la cua.
/// \param hQueue: handler de la cua.
/// \param element: Buffer on deixar l'element.
/// \param waitTime: Temps maxim de bloqueig en ms.
/// \return True si tot es correcte
///
bool osalQueueGet(
	HQueue hQueue,
	void *element,
	unsigned waitTime) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    TickType_t ticks = waitTime == ((unsigned) -1) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
    return xQueueReceive(hQueue, element, ticks) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief Obte un element de la cua. Aquesta versio es per ser cridada
///        d'ins d'una interrupcio.
/// \param hQueue: handler de la cua.
/// \param element: Buffer on deixar l'element.
/// \return True si tot es correcte.
///
bool osalQueueGetISR(
	HQueue hQueue,
	void *element) {

	eosAssert(hQueue != NULL);
	eosAssert(element != NULL);

    BaseType_t priority = pdFALSE;
    return xQueueReceiveFromISR(hQueue, element, &priority) == pdPASS;
}
