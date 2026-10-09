module;


#include "eos.h"


export module Eos.Controllers.Serial;


import Eos.Hardware.Interrupts;
import Eos.Result;
import Eos.Types;
import Eos.System.Core.Task;
import Eos.System.Core.Ticks;


export namespace eos {

	/// \brief Driver per comunicacions serie.
	///
	class SerialDriver {
		public:
			enum class ErrorCode {
				ok,
				busy,
				timeout,
				error,
				errorParameter,
				errorState,
			};
			using Result = SimpleResultX<ErrorCode, ErrorCode::ok>;
			using ResultU32 = ComplexResultX<UInt32, ErrorCode, ErrorCode::ok>;

			enum class State {
                reset,
                ready,
                transmiting,
                receiving
            };

        private:
            State _state;
            Task *_task;
            volatile bool _finished;
            UInt32 _txCount;
            UInt32 _rxCount;

		protected:
            SerialDriver();

            void notifyTxCompleted(uint32_t length, bool irq);
            void notifyRxCompleted(uint32_t length, bool irq);
            State getState() const { return _state; }

			virtual bool onInitialize() = 0;
			virtual bool onDeinitialize() = 0;
			virtual bool onTransmit(const UInt8 *buffer, UInt32 length) = 0;
			virtual bool onReceive(UInt8 *buffer, UInt32 bufferSize) = 0;
			virtual bool onAbort() = 0;

		public:
			virtual ~SerialDriver() = default;

			void initialize();
			void deinitialize();

			Result transmit(const uint8_t *buffer, size_t length);
            Result receive(uint8_t *buffer, size_t bufferSize);
            ResultU32 wait(Ticks blockTime);
            Result abort();

			inline bool isReady() const { return _state == State::ready; }
            inline bool isBusy() const { return _state != State::ready; }
	};
}


using namespace eos;
using namespace eos::hardware::interrupts;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SerialDriver::SerialDriver() :
    _state {State::reset} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SerialDriver::initialize() {

    if (_state == State::reset)
    	if (onInitialize())
    		_state = State::ready;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SerialDriver::deinitialize() {

    if (_state == State::ready)
    	if (onDeinitialize())
    		_state = State::reset;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia una transmissio d'un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: Nombre de bytes en el buffer.
/// \return   El resultat de l'operacio.
///
SerialDriver::Result SerialDriver::transmit(
    const uint8_t *buffer,
    size_t length) {

	if ((buffer == nullptr) ||
		(length == 0))
		return ErrorCode::errorParameter;

	else if (_state == State::ready) {
		_finished = false;
		_task = nullptr;
    	if (onTransmit(buffer, length)) {
    		_state = State::transmiting;
    		return ErrorCode::ok;
    	}
    	else
    		return ErrorCode::error;
    }

    else
    	return ErrorCode::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la recepcio d'un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
SerialDriver::Result SerialDriver::receive(
    uint8_t *buffer,
    size_t bufferSize) {

	if ((buffer == nullptr) ||
		(bufferSize == 0))
		return ErrorCode::errorParameter;

	else if (_state == State::ready) {
		_finished = false;
		_task = nullptr;
    	if (onReceive(buffer, bufferSize)) {
    		_state = State::receiving;
    		return ErrorCode::ok;
    	}
    	else
    		return ErrorCode::error;
    }

    else
    	return ErrorCode::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que finalitzin les operacions pendents.
/// \param    blockTime: Tamps maxim de bloqueig.
/// \return   El nombre de bytes transferits i el resultat.
/// \notes    En cas de timeout, s'aborta la comunicacio.
///
SerialDriver::ResultU32 SerialDriver::wait(
	Ticks blockTime) {

	if (_state == State::receiving) {

		Irq::disableInterrupts();
		if (_finished) {
			Irq::enableInterrupts();
			return {_rxCount};
		}
		else {
			_task = Task::getExecutingTask();
			Irq::enableInterrupts();
			if (Task::waitNotification(true, blockTime))
				return {_rxCount};
			else {
				abort();
				return ErrorCode::timeout;
			}
		}
	}

	else if (_state == State::transmiting) {

		Irq::disableInterrupts();
		if (_finished) {
			Irq::enableInterrupts();
			return {_txCount};
		}
		else {
			_task = Task::getExecutingTask();
			Irq::enableInterrupts();
			if (Task::waitNotification(true, blockTime))
				return {_txCount};
			else {
				abort();
				return ErrorCode::timeout;
			}
		}
	}
	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Aborta l'operacio en curs.
/// \return   El resultat de l'operacio.
///
SerialDriver::Result SerialDriver::abort() {

	if ((_state == State::transmiting) || (_state == State::receiving)) {
		if (onAbort()) {
			_state = State::ready;
			return ErrorCode::ok;
		}
		else
			return ErrorCode::error;
	}
	else
		return ErrorCode::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de transmissio.
/// \param    length: Nombre de bytes transmessos.
/// \param    irq: True si es crida des d'una interrupcio.
///
void SerialDriver::notifyTxCompleted(
	uint32_t length,
	bool irq) {

    if (_state == State::transmiting) {

    	if (_task == nullptr)
    		_finished = true;
    	else
    		_task->raiseNotificationISR();

        _txCount = length;
        _state = State::ready;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de la recepcio.
/// \param    length: Nombre de bytes rebuts
/// \param    irq: True si es crida des d'una interrupcio.
///
void SerialDriver::notifyRxCompleted(
	uint32_t length,
	bool irq) {

    if (_state == State::receiving) {

    	if (_task == nullptr)
    		_finished = true;
    	else
    		_task->raiseNotificationISR();

    	_rxCount = length;
        _state = State::ready;
    }
}
