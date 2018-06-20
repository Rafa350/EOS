#include "osal/osalMsgQueue.h"
#include "osal/osalMemory.h"
#include "FreeRTOS.h"
#include "queue.h"



/// ----------------------------------------------------------------------
/// \brief Crea una cua.
/// \param info: Parametres d'inicialitzacio.
/// \result El handler de la cua. NULL en cas d'error.
///
HMsgQueue osalMsgQueueCreate(
	const MsgQueueInitializeInfo *info) {

	// Comprova que els parametres siguin correctes
	//
	if (info == NULL)
		return NULL;

	// Crea la cua.
	//
	HMsgQueue hMsgQueue = xQueueCreate(info->maxElements, info->elementSize);
	if (hMsgQueue == NULL)
		return NULL;

	// Tot correcte. Retorna el hansler.
	//
    return hMsgQueue;
}


/// ----------------------------------------------------------------------
/// \brief Destrueix una cua.
/// \param hMsgQueue: El handler de la cua.
///
void osalMsgQueueDestroy(
	HMsgQueue hMsgQueue) {

	// Comprova que els parametres siguin corerectes.
	//
	if (hMsgQueue == NULL)
		return;

	// Destrueix la cua.
	//
	vQueueDelete(hMsgQueue);
}


/// ----------------------------------------------------------------------
/// \brief Buida el contingut de la cua.
/// \param hMsgQueue: El handler de la cua.
///
void osalMsgQueueClear(
	HMsgQueue hMsgQueue) {

	// Comprova que els parametres siguin corretes.
	//
	if (hMsgQueue == NULL)
		return;

	// Borra el contingut de las cua.
	//
	xQueueReset(hMsgQueue);
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element a la cua.
/// \param hMsgQueue: El handler de la cua.
/// \param element: El element a afeigir.
/// \param waitTime: Temps maxim de bloqueig en ms.
/// \return True si tot es correcte.
///
bool osalMsgQueuePut(
	HMsgQueue hMsgQueue,
	const void *element,
	unsigned waitTime) {

	// Comprova que els parametres siguin correctes.
	//
	if (hMsgQueue == NULL)
		return false;
	if (element == NULL)
		return false;

	// Afegeix l'element a la cua
	//
    TickType_t ticks = waitTime == ((unsigned) -1) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
    if (xQueueSendToBack(hMsgQueue, element,  ticks) != pdPASS)
    	return false;

    // Tot correcte. Retorna true.
    //
    return true;
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element a la cua. Aquesta versio es per ser cridada
///		   d'ins d'una interrupcio.
/// \param hMsgQueue: El handler de la cua.
/// \param element: El element a afeigir.
/// \return True si tot es correcte
///
bool osalQueuePutISR(
	HMsgQueue hMsgQueue,
	const void *element) {

	// Comprova que els parametres siguin correctes.
	//
	if (hMsgQueue == NULL)
		return false;
	if (element == NULL)
		return false;

	// Afegeix l'elelemt.
	//
    BaseType_t priority = pdFALSE;
    if (xQueueSendFromISR(hMsgQueue, element, &priority) != pdPASS)
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
bool osalMsgQueueGet(
	HMsgQueue hMsgQueue,
	void *element,
	unsigned waitTime) {

	// Comprova que els parametres siguin correctes.
	//
	if (hMsgQueue == NULL)
		return false;
	if (element == NULL)
		return false;

	// Obte l'element de la cua.
	//
    TickType_t ticks = waitTime == ((unsigned) -1) ? portMAX_DELAY : waitTime / portTICK_PERIOD_MS;
    if (xQueueReceive(hMsgQueue, element, ticks) != pdPASS)
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
	HMsgQueue hMsgQueue,
	void *element) {

	// Comprova si els parametres son correctes.
	//
	if (hMsgQueue == NULL)
		return false;
	if (element == NULL)
		return false;

	// Obte l'element de la cua.
	//
    BaseType_t priority = pdFALSE;
    if (xQueueReceiveFromISR(hMsgQueue, element, &priority) != pdPASS)
		return false;

    // Tot correcte. Retorna true.
    //
	return true;
}
