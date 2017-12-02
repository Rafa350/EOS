#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalQueue.h"

#include "FreeRTOS.h"
#include "queue.h"


/// ----------------------------------------------------------------------
/// \brief Crea una cua.
/// \param info: Parametres d'inicialitzacio.
/// \return El handler de la cua.
///
QueueHandler osalQueueCreate(
	const QueueInitializeInfo *info) {

	eosArgumentIsNotNull(info);

	void *handle = xQueueCreate(info->maxElements, info->elementSize);

    return handle;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix una cua.
/// \param queue: El handler de la cua.
///
void osalQueueDestroy(
	QueueHandler queue) {

	eosArgumentIsNotNull(queue);

	vQueueDelete(queue);
}


/// ----------------------------------------------------------------------
/// \brief Buida el contingut de la cua.
/// \param queue: El handler de la cua.
///
void osalQueueClear(
	QueueHandler queue) {

	eosArgumentIsNotNull(queue);

	xQueueReset(queue);
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element a la cua.
/// \param queue: El handler de la cua.
/// \param element: El element a afeigir.
/// \param blockTime: Temps maxim de bloqueig en ms.
/// \return True si s'ha afeigit l'element a la cua. False en cas contrari.
///
bool osalQueuePut(
	QueueHandler queue,
	const void *element,
	unsigned blockTime) {

	eosArgumentIsNotNull(queue);
	eosArgumentIsNotNull(element);

    TickType_t ticks = blockTime == ((unsigned) -1) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
    return xQueueSendToBack(queue, element,  ticks) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element a la cua. Aquesta versio es per ser cridada
///		   d'ins d'una interrupcio.
/// \param queue: El handler de la cua.
/// \param element: El element a afeigir.
/// \return True si s'ha afeigit l'element a la cua. False en cas contrari.
///
bool osalQueuePutISR(
	QueueHandler queue,
	const void *element) {

	eosArgumentIsNotNull(queue);
    eosArgumentIsNotNull(element);

    BaseType_t priority = pdFALSE;
    return xQueueSendFromISR(queue, element, &priority) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief Obte un element de la cua.
/// \param queue: handler de la cua.
/// \param element: Buffer on deixar l'element.
/// \param blockTime: Temps maxim de bloqueig en ms.
/// \return True si s'ha obtingut l'element de la cua. False en cas contrari.
///
bool osalQueueGet(
	QueueHandler queue,
	void *element,
	unsigned blockTime) {

	eosArgumentIsNotNull(queue);
    eosArgumentIsNotNull(element);

    TickType_t ticks = blockTime == ((unsigned) -1) ? portMAX_DELAY : blockTime / portTICK_PERIOD_MS;
    return xQueueReceive(queue, element, ticks) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief Obte un element de la cua. Aquesta versio es per ser cridada
///        d'ins d'una interrupcio.
/// \param queue: handler de la cua.
/// \param element: Buffer on deixar l'element.
/// \return True si s'ha obtingut l'element de la cua. False en cas contrari.
///
bool osalQueueGetISR(
	QueueHandler queue,
	void *element) {

	eosArgumentIsNotNull(queue);
    eosArgumentIsNotNull(element);

    BaseType_t priority = pdFALSE;
    return xQueueReceiveFromISR(queue, element, &priority) == pdPASS;
}
