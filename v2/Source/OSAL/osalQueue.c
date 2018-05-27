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

	// Comprova que els parametres siguin correctes
	//
	if (info == NULL)
		return NULL;

	// Crea la cua.
	//
	HQueue hQueue = xQueueCreate(info->maxElements, info->elementSize);
	if (hQueue == NULL)
		return NULL;

	// Tot correcte. Retorna el hansler.
	//
    return hQueue;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix una cua.
/// \param hQueue: El handler de la cua.
///
void osalQueueDestroy(
	HQueue hQueue) {

	// Comprova que els parametres siguin corerectes.
	//
	if (hQueue == NULL)
		return;

	// Destrueix la cua.
	//
	vQueueDelete(hQueue);
}


/// ----------------------------------------------------------------------
/// \brief Buida el contingut de la cua.
/// \param hQueue: El handler de la cua.
///
void osalQueueClear(
	HQueue hQueue) {

	// Comprova que els parametres siguin corretes.
	//
	if (hQueue == NULL)
		return;

	// Borra el contingut de las cua.
	//
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

	// Comprova que els parametres siguin correctes.
	//
	if (hQueue == NULL)
		return false;
	if (element == NULL)
		return false;

	// Afegeix l'element a la cua
	//
    TickType_t ticks = waitTime == ((unsigned) -1) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
    if (xQueueSendToBack(hQueue, element,  ticks) != pdPASS)
    	return false;

    // Tot correcte. Retorna true.
    //
    return true;
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

	// Comprova que els parametres siguin correctes.
	//
	if (hQueue == NULL)
		return false;
	if (element == NULL)
		return false;

	// Afegeix l'elelemt.
	//
    BaseType_t priority = pdFALSE;
    if (xQueueSendFromISR(hQueue, element, &priority) != pdPASS)
    	return false;

    // Tot correcte. Retorna true.
    //
    return true;
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

	// Comprova que els parametres siguin correctes.
	//
	if (hQueue == NULL)
		return false;
	if (element == NULL)
		return false;

	// Obte l'element de la cua.
	//
    TickType_t ticks = waitTime == ((unsigned) -1) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
    if (xQueueReceive(hQueue, element, ticks) != pdPASS)
    	return false;

    // Tot correcte. Retorna true.
    //
    return true;
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

	// Comprova si els parametres son correctes.
	//
	if (hQueue == NULL)
		return false;
	if (element == NULL)
		return false;

	// Obte l'element de la cua.
	//
    BaseType_t priority = pdFALSE;
    if (xQueueReceiveFromISR(hQueue, element, &priority) != pdPASS)
		return false;

    // Tot correcte. Retorna true.
    //
	return true;
}
