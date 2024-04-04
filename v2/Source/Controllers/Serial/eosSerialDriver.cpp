#include "eos.h"
#include "Controllers/Serial/eosSerialDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SerialDriver::SerialDriver() :

	_state {State::reset} {
}


/// ----------------------------------------------------------------------
/// \brief    Transmiteix un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: El nombre de bytes a transmetre.
/// \return   True si tot es correcte.
///
bool SerialDriver::transmit(
	const uint8_t *buffer,
	unsigned length) {

	return isBusy() ? false : transmitImpl(buffer, length);
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    buffer: El buffer de recepcio.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   True si tot es correcte.
///
bool SerialDriver::receive(
	uint8_t *buffer,
	unsigned bufferSize) {

	return isBusy() ? false : receiveImpl(buffer, bufferSize);
}


/// ----------------------------------------------------------------------
/// \brief    Aborta la comunicacio.
/// \return   True si es correcte.
///
bool SerialDriver::abort() {

    return abortImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SerialDriver::initializeImpl() {

	_state = State::ready;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SerialDriver::deinitializeImpl() {

	_state = State::reset;
}


/// ----------------------------------------------------------------------
/// \brief    Aborta la comunicacio.
/// \return   True si es correcte.
///
bool SerialDriver::abortImpl() {

    _state = State::ready;
    return true;
}


