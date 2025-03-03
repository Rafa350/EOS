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
		return Results::success;
	}
	else
		return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Deinicialitza el stream.
/// \return   El resultat de l'operacio.
///
Result SerialStream::deinitialize() {

	if (_drvSerial != nullptr) {
		_drvSerial->deinitialize();
		_drvSerial = nullptr;
		return Results::success;
	}
	else
		return Results::error;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el stream.
/// \param    data: El bloc de dades a escriure.
/// \param    length: El nombre de bytes a escriure.
/// \param    count: El nombre de bytes escrits.
/// \return   El resultat de l'operacio.
//
Result SerialStream::write(
	const uint8_t *data,
	unsigned length,
	unsigned *count) {

	if (_drvSerial == nullptr)
		return Results::error;

	else {
		_drvSerial->transmit(data, length);

		auto result = _drvSerial->wait(_txTimeout);
		if (result.isSuccess()) {

			if (count != nullptr)
				*count = result;

			return Results::success;
		}
		else {
			_drvSerial->abort();
			return Results::timeout;
		}
	}
}


/// ---------------------------------------------------------------------
/// \brief    Llegeix dades des del stream.
/// \param    data: Bloc on deixar les dades.
/// \param    size: Tamany del bloc en bytes.
/// \param    count: El nombre de bytes lleigits.
/// \return   El resultat de l'operacio.
///
Result SerialStream::read(
	uint8_t *data,
	unsigned size,
	unsigned *count) {

	if (_drvSerial == nullptr)
		return Results::error;

	else {
		_drvSerial->receive(data, size);

		auto result = _drvSerial->wait(_rxTimeout);
		if (result.isSuccess()) {

			if (count != nullptr)
				*count = result;

			return Results::success;
		}
		else {
			_drvSerial->abort();
			return Results::timeout;
		}
	}
}
