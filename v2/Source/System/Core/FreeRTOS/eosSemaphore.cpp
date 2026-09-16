module;


#include "eos.h"
#include "eosTime.h"
#include "FreeRTOS.h"
#include "semphr.h"


export module Eos.System.Core.Semaphore;


export import Eos.Result;


import Eos.System.Core.RTOSUtils;


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
#if (configSUPPORT_STATIC_ALLOCATION == 1)
			StaticSemaphore_t _data;
#endif
        private:
			[[nodiscard]] SemaphoreHandle_t createHandler();

        public:
            Semaphore();
			Semaphore(const Semaphore&) = delete;
			Semaphore(Semaphore&&) = delete;
            ~Semaphore();

			Semaphore& operator = (const Semaphore &other) = delete;
			Semaphore& operator = (Semaphore &&other) = delete;

            [[nodiscard]] Result wait(Time blockTime) const;
            void release() const;
            void releaseISR() const;
	};
}


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
///
eos::Semaphore::Semaphore():
	_handler {createHandler()} {

}


/// ---------------------------------------------------------------------------
/// @brief    Destructor.
///
eos::Semaphore::~Semaphore() {

	vSemaphoreDelete(_handler);
}


/// ---------------------------------------------------------------------------
/// @brief    Crea el handler d'un semaforo.
/// @return   El handler.
///
SemaphoreHandle_t eos::Semaphore::createHandler() {

#if (configSUPPORT_STATIC_ALLOCATION == 1)
	SemaphoreHandle_t handler = xSemaphoreCreateBinaryStatic(&_data);
#else
	SemaphoreHandle_t handler = xSemaphoreCreateBinary();
#endif
	return  handler;
}


/// ---------------------------------------------------------------------------
/// @brief    Espera el semaforo.
/// @param    blockTime: Tamps de bloqueig.
/// @return   True si es correcte. False en cas d'error o timeout.
///
eos::Semaphore::Result eos::Semaphore::wait(
	Time blockTime) const {

	return xSemaphoreTake(_handler, toTicks(blockTime)) == pdTRUE ?
		ErrorCode::ok :
		ErrorCode::timeout;
}


/// ---------------------------------------------------------------------------
/// @brief    Allivera el semaforo.
///
void eos::Semaphore::release() const {

	xSemaphoreGive(_handler);
}


/// ---------------------------------------------------------------------------
/// @brief    Allivera el semaforo d'ins d'una funcio ISR.
///
void eos::Semaphore::releaseISR() const {

	portBASE_TYPE taskWoken = pdFALSE;
	if (xSemaphoreGiveFromISR(_handler, &taskWoken) == pdPASS)
		portEND_SWITCHING_ISR(taskWoken);
}
