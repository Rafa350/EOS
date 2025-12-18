#include "eos.h"
#include "eosAssert.h"
#include "System/IO/eosSerialStream.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte.
///
SerialStream::SerialStream() :

	_drvSerial {nullptr} {
}


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte i l'inicialitza.
/// \param    drvSerial: El driver del comunicacions serie.
///
SerialStream::SerialStream(
	SerialDriver *drvSerial) :

	_drvSerial {nullptr} {

	initialize(drvSerial);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el stream.
/// \param    drvSerial:: El driver del canal serie.
/// \return   El resultat de l'operacio.
///
Result SerialStream::initialize(
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
Result SerialStream::deinitialize() {

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
/// \param    data: El bloc de dades a escriure.
/// \param    length: El nombre de bytes a escriure.
/// \return   El nombre de bytes transmissos, i resultat de l'operacio.
//
ResultU32 SerialStream::write(
	const uint8_t *data,
	unsigned length) {

	if ((data == nullptr) || (length == 0))
		return ResultU32::ErrorCodes::errorParameter;

	else if (_drvSerial == nullptr)
		return ResultU32::ErrorCodes::errorState;

	else {
		if (_drvSerial->transmit(data, length).is(Result::ErrorCodes::busy))
			return ResultU32::ErrorCodes::busy;
		else {
			auto result = _drvSerial->wait(_txTimeout);
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
/// \param    data: Bloc on deixar les dades.
/// \param    size: Tamany del bloc en bytes.
/// \return   El nombre de bytes transmessos, i el resultat de l'operacio.
///
ResultU32 SerialStream::read(
	uint8_t *data,
	unsigned size) {

	if ((data == nullptr) || (size == 0))
		return ResultU32::ErrorCodes::errorParameter;

	if (_drvSerial == nullptr)
		return ResultU32::ErrorCodes::error;

	else {
		if (_drvSerial->receive(data, size).is(Result::ErrorCodes::busy))
			return ResultU32::ErrorCodes::busy;
		else {
			auto result = _drvSerial->wait(_rxTimeout);
			if (result.isSuccess())
				return {ResultU32::ErrorCodes::ok, result.value()};
			else
				return ResultU32::ErrorCodes::timeout;
		}
	}
}
