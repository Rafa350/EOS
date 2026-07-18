#include "eos.h"
#include "eosAssert.h"
#include "RTOS/rtosTime.h"
#include "RTOS/rtosQueue.h"

#include "FreeRTOS.h"
#include "queue.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    elementSize: Tamany en bytes de cada elment en la cua.
/// \param    capacity: El nombre d'elements que caben en la cua.
///
rtos::Queue::Queue(
	uint32_t elementSize,
	uint32_t capacity):

	_handler {xQueueCreate(capacity, elementSize)} {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
rtos::Queue::~Queue() {

	vQueueDelete(static_cast<QueueHandle_t>(_handler));
}


/// ----------------------------------------------------------------------
/// \brief    Buida el contingut de la cua.
///
void rtos::Queue::clear() const {

	xQueueReset(static_cast<QueueHandle_t>(_handler));
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un element a la cua
/// \param    element: L'element a afeigir.
/// \param    blockTime: Tammps maxim de bloqueig.
/// \return   True si tot es correcte.
///
bool rtos::Queue::put(
	const void *element,
	eos::Time blockTime) const {

    return xQueueSendToBack(static_cast<QueueHandle_t>(_handler), element,
    	rtos::toTicks(blockTime)) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un element a la cua. Utilitzar unicament en ISR.
/// \param    element: L'element a afeigir.
/// \return   True si tot es correcte.
///
bool rtos::Queue::putISR(
	const void *element) const {

    BaseType_t taskWoken = pdFALSE;
    auto result = xQueueSendFromISR(static_cast<QueueHandle_t>(_handler),
    		element, &taskWoken) == pdPASS;
    if (result)
    	portEND_SWITCHING_ISR(taskWoken);

    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua.
/// \param    element: Buffer per l'exelent a extreure
/// \param    blockTime: Tamps maxim de bloqueig.
/// \return   TYrue si tot es correcte.
///
bool rtos::Queue::get(
	void *element,
	eos::Time blockTime) const {

    return xQueueReceive(static_cast<QueueHandle_t>(_handler), element,
    	rtos::toTicks(blockTime)) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua. Utilitzar unicament en ISR.
/// \param    element: Buffer per l'exelent a extreure.
/// \return   TYrue si tot es correcte.
///
bool rtos::Queue::getISR(
	void *element) const {

    BaseType_t taskWoken = pdFALSE;
    bool result = xQueueReceiveFromISR(static_cast<QueueHandle_t>(_handler),
    	element, &taskWoken) == pdPASS;
    if (result)
    	portEND_SWITCHING_ISR(taskWoken);

    return result;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua, pero sense retirar-lo.
/// \param    element: Buffer per l'element a extreure.
/// \param    blockTime: Tamps maxim de bloqueig.
/// \return   True si tot es correcte.
///
bool rtos::Queue::peek(
	void *element,
	eos::Time blockTime) const {

    return xQueuePeek(static_cast<QueueHandle_t>(_handler), element,
    	rtos::toTicks(blockTime)) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua, pero sense retirar-lo.
///           Utilitzar unicament en un ISR.
/// \param    element: Buffer per l'element a extreure.
/// \return   True si tot es correcte.
///
bool rtos::Queue::peekISR(
	void *element) const {

    return xQueuePeekFromISR(static_cast<QueueHandle_t>(_handler),
    	element) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la cua es buida
/// \return   True si es buida.
///
bool rtos::Queue::isEmpty() const {

	return getCount() == 0;
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si la cua es buida. Untilitzar unicament en ISR.
/// \return   True si es buida.
///
bool rtos::Queue::isEmptyISR() const {

	return getCountISR() == 0;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre d'elementsa en la cua.
/// \returnn  El nombre d'elements.
///
uint32_t rtos::Queue::getCount() const {

	return uxQueueMessagesWaiting(static_cast<QueueHandle_t>(_handler));
}


/// ----------------------------------------------------------------------
/// \brief    Obte el nombre d'elementsa en la cua. Utilitzar
///           unicament en ISR.
/// \returnn  El nombre d'elements.
///
uint32_t rtos::Queue::getCountISR() const {

	return uxQueueMessagesWaitingFromISR(
			static_cast<QueueHandle_t>(_handler));
}
