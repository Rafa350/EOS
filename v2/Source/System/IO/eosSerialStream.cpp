#include "eos.h"
#include "eosAssert.h"
#include "System/IO/eosSerialStream.h"


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte.
///
eos::SerialStream::SerialStream() :

	_drvSerial {nullptr} {
}


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte i l'inicialitza.
/// \param    drvSerial: El driver del comunicacions serie.
///
eos::SerialStream::SerialStream(
	SerialDriver *drvSerial) :

	_drvSerial {nullptr} {

	initialize(drvSerial);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el stream.
/// \param    drvSerial:: El driver del canal serie.
/// \return   El resultat de l'operacio.
///
eos::Result eos::SerialStream::initialize(
	SerialDriver *drvSerial) {

	eosAssert(drvSerial != nullptr);
	eosAssert(_drvSerial == nullptr);

	if (_drvSerial == nullptr) {
		_drvSerial = drvSerial;
		_drvSerial->initialize();
		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Deinicialitza el stream.
/// \return   El resultat de l'operacio.
///
eos::Result eos::SerialStream::deinitialize() {

	if (_drvSerial != nullptr) {
		_drvSerial->deinitialize();
		_drvSerial = nullptr;
		return Result::ErrorCodes::ok;
	}
	else
		return Result::ErrorCodes::error;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el stream.
/// \param    buffer: El buffer de dades a escriure.
/// \param    length: El nombre de bytes a escriure.
/// \return   El nombre de bytes transmissos, i resultat de l'operacio.
//
eos::ResultU32 eos::SerialStream::write(
	const uint8_t *buffer,
	uint32_t length) {

	if ((buffer == nullptr) || (length == 0))
		return ResultU32::ErrorCodes::errorParameter;

	else if (_drvSerial == nullptr)
		return ResultU32::ErrorCodes::errorState;

	else {
		if (_drvSerial->transmit(buffer, length).is(Result::ErrorCodes::busy))
			return ResultU32::ErrorCodes::busy;
		else {
			auto result = _drvSerial->wait(_txTimeout.toMiliseconds());
			if (result.isSuccess())
				return {ResultU32::ErrorCodes::ok, result.value()};
			else {
				_drvSerial->abort();
				return ResultU32::ErrorCodes::timeout;
			}
		}
	}
}


/// ---------------------------------------------------------------------
/// \brief    Llegeix dades des del stream.
/// \param    buffer: Buffer on deixar les dades.
/// \param    bufferSize: Tamany del bloc en bytes.
/// \return   El nombre de bytes transmessos, i el resultat de l'operacio.
///
eos::ResultU32 eos::SerialStream::read(
	uint8_t *buffer,
	uint32_t bufferSize) {

	if ((buffer == nullptr) || (bufferSize == 0))
		return ResultU32::ErrorCodes::errorParameter;

	if (_drvSerial == nullptr)
		return ResultU32::ErrorCodes::error;

	else {
		if (_drvSerial->receive(buffer, bufferSize).is(Result::ErrorCodes::busy))
			return ResultU32::ErrorCodes::busy;
		else {
			auto result = _drvSerial->wait(_rxTimeout.toMiliseconds());
			if (result.isSuccess())
				return {ResultU32::ErrorCodes::ok, result.value()};
			else
				return ResultU32::ErrorCodes::timeout;
		}
	}
}
