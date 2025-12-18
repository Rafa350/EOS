#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Serial/eosSerialDriver.h"
#include "HTL/htlINT.h"
#include "System/Core/eosTask.h"


using namespace eos;


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
Result SerialDriver::transmit(
    const uint8_t *buffer,
    unsigned length) {

	if ((buffer == nullptr) ||
		(length == 0))
		return Result::ErrorCodes::errorParameter;

	else if (_state == State::ready) {
		_finished = false;
		_task = nullptr;
    	if (onTransmit(buffer, length)) {
    		_state = State::transmiting;
    		return Result::ErrorCodes::ok;
    	}
    	else
    		return Result::ErrorCodes::error;
    }

    else
    	return Result::ErrorCodes::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la recepcio d'un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   El resultat de l'operacio.
///
Result SerialDriver::receive(
    uint8_t *buffer,
    unsigned bufferSize) {

	if ((buffer == nullptr) ||
		(bufferSize == 0))
		return Result::ErrorCodes::errorParameter;

	else if (_state == State::ready) {
		_finished = false;
		_task = nullptr;
    	if (onReceive(buffer, bufferSize)) {
    		_state = State::receiving;
    		return Result::ErrorCodes::ok;
    	}
    	else
    		return Result::ErrorCodes::error;
    }

    else
    	return Result::ErrorCodes::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Espera que finalitzin les operacions pendents.
/// \param    waitTime: Tamps d'espera.
/// \return   El nombre de bytes transferits i el resultat.
/// \notes    En cas de timeout, s'aborta la comunicacio.
///
ResultU32 SerialDriver::wait(
	unsigned waitTime) {

	if (_state == State::receiving) {

		htl::irq::disableInterrupts();
		if (_finished) {
			htl::irq::enableInterrupts();
			return {ResultU32::ErrorCodes::ok, _rxCount};
		}
		else {
			_task = Task::getExecutingTask();
			htl::irq::enableInterrupts();
			if (Task::waitNotification(true, waitTime))
				return {ResultU32::ErrorCodes::ok, _rxCount};
			else {
				abort();
				return ResultU32::ErrorCodes::timeout;
			}
		}
	}

	else if (_state == State::transmiting) {

		htl::irq::disableInterrupts();
		if (_finished) {
			htl::irq::enableInterrupts();
			return {ResultU32::ErrorCodes::ok, _txCount};
		}
		else {
			_task = Task::getExecutingTask();
			htl::irq::enableInterrupts();
			if (Task::waitNotification(true, waitTime))
				return {ResultU32::ErrorCodes::ok, _txCount};
			else {
				abort();
				return ResultU32::ErrorCodes::timeout;
			}
		}
	}
	else
		return ResultU32::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Aborta l'operacio en curs.
/// \return   El resultat de l'operacio.
///
Result SerialDriver::abort() {

	if ((_state == State::transmiting) || (_state == State::receiving)) {
		if (onAbort()) {
			_state = State::ready;
			return Result::ErrorCodes::ok;
		}
		else
			return Result::ErrorCodes::error;
	}
	else
		return Result::ErrorCodes::errorState;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de transmissio.
/// \param    length: Nombre de bytes transmessos.
/// \param    irq: True si es crida des d'una interrupcio.
///
void SerialDriver::notifyTxCompleted(
	unsigned length,
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
	unsigned length,
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
