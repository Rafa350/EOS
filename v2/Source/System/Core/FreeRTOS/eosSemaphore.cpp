module;


#include "eos.h"
#include "RTOS/rtosTime.h"
#include "FreeRTOS.h"
#include "semphr.h"


export module Eos.System.Core.Semaphore;


export import Eos.Result;


export namespace eos {

	class Semaphore final {
		public:
			enum class ErrorCode {
				ok,
				timeout,
				error
			};
			using Result = SimpleResultX<ErrorCode, ErrorCode::ok>;

        private:
			SemaphoreHandle_t _handler;

        public:
            Semaphore();
			Semaphore(const Semaphore&);
			Semaphore(Semaphore&&);
            ~Semaphore();

			Semaphore& operator = (const Semaphore &other);
			Semaphore& operator = (Semaphore &&other);

            Result wait(Time blockTime) const;
            void release() const;
            void releaseISR() const;
	};
}


/// ---------------------------------------------------------------------------
/// \brief    Constructor.
///
eos::Semaphore::Semaphore():
	_handler {xSemaphoreCreateBinary()} {

}


/// ---------------------------------------------------------------------------
/// \brief    Constructor de copia.
///
eos::Semaphore::Semaphore(
	const Semaphore &other):

	_handler {other._handler} {

}


/// ---------------------------------------------------------------------------
/// \brief    Constructor de moviment.
///
eos::Semaphore::Semaphore(
	Semaphore &&other) {

	_handler = other._handler;
	other._handler = nullptr;
}


/// ---------------------------------------------------------------------------
/// \brief    Destructor.
///
eos::Semaphore::~Semaphore() {

	if (_handler != nullptr)
		vSemaphoreDelete(_handler);
}


/// ---------------------------------------------------------------------------
/// @brief 
/// @param other 
/// @return 
///
eos::Semaphore& eos::Semaphore::operator = (
	const eos::Semaphore &other) {

	return *this;
}


/// ---------------------------------------------------------------------------
/// @brief 
/// @param other 
/// @return 
///
eos::Semaphore& eos::Semaphore::operator = (
	eos::Semaphore &&other) {

	return *this;
}


/// ---------------------------------------------------------------------------
/// \brief    Espera el semaforo.
/// \param    blockTime: Tamps de bloqueig.
/// \return   True si es correcte. False en cas d'error o timeout.
///
eos::Semaphore::Result eos::Semaphore::wait(
	eos::Time blockTime) const {

	return xSemaphoreTake(_handler, rtos::toTicks(blockTime)) == pdTRUE ?
		ErrorCode::ok :
		ErrorCode::timeout;
}


/// ---------------------------------------------------------------------------
/// \brief    Allivera el semaforo.
///
void eos::Semaphore::release() const {

	xSemaphoreGive(_handler);
}


/// ---------------------------------------------------------------------------
/// \brief    Allivera el semaforo d'ins d'una funcio ISR.
///
void eos::Semaphore::releaseISR() const {

	portBASE_TYPE taskWoken = pdFALSE;
	if (xSemaphoreGiveFromISR(_handler, &taskWoken) == pdPASS)
		portEND_SWITCHING_ISR(taskWoken);
}
