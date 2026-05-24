#include "RTOS/rtosMiliseconds.h"
#include "RTOS/rtosQueue.h"
#include "RTOS/rtosTicks.h"

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
	Miliseconds blockTime) const {

    return xQueueSendToBack(static_cast<QueueHandle_t>(_handler), element,
    	blockTime.asTicks()) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un element a la cua d'ins d'un ISR
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
/// \param    element: L'exelent a extreure
/// \param    blockTime: Tamps maxim de bloqueig.
/// \return   TYrue si tot es correcte.
///
bool rtos::Queue::get(
	void *element,
	Miliseconds blockTime) const {

    return xQueueReceive(static_cast<QueueHandle_t>(_handler), element,
    	blockTime.asTicks()) == pdPASS;
}


/// ----------------------------------------------------------------------
/// \brief    Obte un element de la cua d'ins d'un ISR
/// \param    element: L'exelent a extreure
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


bool rtos::Queue::peek(
	void *element,
	Miliseconds blockTime) const {

    return xQueuePeek(static_cast<QueueHandle_t>(_handler), element,
    	blockTime.asTicks()) == pdPASS;
}


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
/// \brief    Comprova si la cua es buida d'ind d'un ISR
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
/// \brief    Obte el nombre d'elementsa en la cua, d'ins d'un ISR
/// \returnn  El nombre d'elements.
///
uint32_t rtos::Queue::getCountISR() const {

	return uxQueueMessagesWaitingFromISR(
			static_cast<QueueHandle_t>(_handler));
}
