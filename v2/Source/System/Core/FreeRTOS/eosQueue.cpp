module;


#include "eos.h"

#include "FreeRTOS.h"
#include "queue.h"


export module Eos.System.Core.Queue;


import Eos.Types;
import Eos.System.Core.Ticks;


export namespace eos {

    /// \brief Cua
    /// \param T_: Tipus del element en la cua.
	///
    template <typename T_>
    class Queue final: private NonCopyableClass {
    	private:
            QueueHandle_t _handler;

        private:
            QueueHandle_t createHandle(uint32_t capacity);

        public:
            Queue(uint32_t capacity);
            ~Queue();

            void clear() const;

            bool push(const T_ &element, Ticks blockTime) const;
            bool pushISR(const T_ &element) const;
            bool pop(T_ &element, Ticks blockTime) const;
            bool popISR(T_ &element) const;
            bool peek(T_ &element, Ticks blockTime) const;
            bool peekISR(T_ &element) const;

            [[nodiscard]] bool isEmpty() const;
            [[nodiscard]] bool isEmptyISR() const;

            [[nodiscard]] uint32_t getCount() const;
            [[nodiscard]] uint32_t getCountISR() const;
    };

}



/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @tparam   T_: El tipus del element de la cua.
/// @param    capacity: El nombre d'elements que caben en la cua.
///
template <typename T_>
eos::Queue<T_>::Queue(
	uint32_t capacity):

	_handler {createHandle(capacity)} {

}


/// ---------------------------------------------------------------------------
/// @brief    Destructor.
/// @tparam   T_: El tipus del element de la cua.
///
template <typename T_>
eos::Queue<T_>::~Queue() {

	vQueueDelete(_handler);
}


/// ---------------------------------------------------------------------------
/// @brief    Crea ela handler de la cua.
/// @tparam   T_: El tipus del element de la cua.
/// @param    capacity : El nombre d'elemments que caben en la cua.
/// @return   El handler de la cua.
///
template <typename T_>
QueueHandle_t eos::Queue<T_>::createHandle(
    uint32_t capacity) {

	return xQueueCreate(capacity, sizeof(T_));
}


/// ---------------------------------------------------------------------------
/// @brief    Buida la cua.
/// @tparam   T_: El tipus del element de la cua.
///
template <typename T_>
void eos::Queue<T_>::clear() const {

	xQueueReset(_handler);
}


/// ---------------------------------------------------------------------------
/// @brief    Afegeix un element a la cua
/// @tparam   T_: El tipus del element de la cua.
/// @param    element: L'element a afeigir.
/// @param    blockTime: Tammps maxim de bloqueig.
/// @return   True si tot es correcte.
///
template <typename T_>
bool eos::Queue<T_>::push(
	const T_ &element,
	Ticks blockTime) const {

    return xQueueSendToBack(
        _handler,
        static_cast<const void*>(&element),
        static_cast<TickType_t>(blockTime)) == pdPASS;
}


/// ---------------------------------------------------------------------------
/// @brief    Afegeix un element a la cua. Utilitzar unicament en ISR.
/// @tparam   T_: El tipus del element de la cua.
/// @param    element: L'element a afeigir.
/// @return   True si tot es correcte.
///
template <typename T_>
bool eos::Queue<T_>::pushISR(
	const T_ &element) const {

    BaseType_t taskWoken = pdFALSE;

    bool result = xQueueSendToBackFromISR(
        _handler,
        static_cast<const void*>(&element),
        &taskWoken) == pdPASS;

    if (result)
    	portEND_SWITCHING_ISR(taskWoken);

    return result;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte un element de la cua.
/// @tparam   T_: El tipus del element de la cua.
/// @param    element: Buffer per l'exelent a extreure
/// @param    blockTime: Tamps maxim de bloqueig.
/// @return   TYrue si tot es correcte.
///
template <typename T_>
bool eos::Queue<T_>::pop(
	T_ &element,
	Ticks blockTime) const {

    return xQueueReceive(
        _handler,
        static_cast<void*>(&element),
    	static_cast<TickType_t>(blockTime)) == pdPASS;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte un element de la cua. Utilitzar unicament en ISR.
/// @tparam   T_: El tipus del element de la cua.
/// @param    element: Buffer per l'exelent a extreure.
/// @return   TYrue si tot es correcte.
///
template <typename T_>
bool eos::Queue<T_>::popISR(
	T_ &element) const {

    BaseType_t taskWoken = pdFALSE;

    bool result = xQueueReceiveFromISR(
        _handler,
        static_cast<void*>(&element),
        &taskWoken) == pdPASS;

        if (result)
    	portEND_SWITCHING_ISR(taskWoken);

    return result;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte un element de la cua, pero sense retirar-lo.
/// @tparam   T_: El tipus del element de la cua.
/// @param    element: Buffer per l'element a extreure.
/// @param    blockTime: Tamps maxim de bloqueig.
/// @return   True si tot es correcte.
///
template <typename T_>
bool eos::Queue<T_>::peek(
	T_ &element,
	Ticks blockTime) const {

    return xQueuePeek(
        _handler,
        static_cast<void*>(&element),
    	static_cast<TickType_t>(blockTime)) == pdPASS;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte un element de la cua, pero sense retirar-lo.
///           Utilitzar unicament en un ISR.
/// @tparam   T_: El tipus del element de la cua.
/// @param    element: Buffer per l'element a extreure.
/// @return   True si tot es correcte.
///
template <typename T_>
bool eos::Queue<T_>::peekISR(
	T_ &element) const {

    return xQueuePeekFromISR(
        _handler,
        static_cast<void*>(&element)) == pdPASS;
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si la cua es buida
/// @tparam   T_: El tipus del element de la cua.
/// @return   True si es buida.
///
template <typename T_>
bool eos::Queue<T_>::isEmpty() const {

	return getCount() == 0;
}


/// ---------------------------------------------------------------------------
/// @brief    Comprova si la cua es buida. Untilitzar unicament en ISR.
/// @tparam   T_: El tipus del element de la cua.
/// @return   True si es buida.
///
template <typename T_>
bool eos::Queue<T_>::isEmptyISR() const {

	return getCountISR() == 0;
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el nombre d'elementsa en la cua.
/// @tparam   T_: El tipus del element de la cua.
/// @return   El nombre d'elements.
///
template <typename T_>
uint32_t eos::Queue<T_>::getCount() const {

	return uxQueueMessagesWaiting(_handler);
}


/// ---------------------------------------------------------------------------
/// @brief    Obte el nombre d'elementsa en la cua. Utilitzar
///           unicament en ISR.
/// @tparam   T_: El tipus del element de la cua.
/// @return   El nombre d'elements.
///
template <typename T_>
uint32_t eos::Queue<T_>::getCountISR() const {

	return uxQueueMessagesWaitingFromISR(_handler);
}
