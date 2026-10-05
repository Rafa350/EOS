module;


#include "eos.h"
#include "eosAssert.h"
#include "eosResults.h"


export module Eos.System.IO.Streams.Serial;


export import Eos.System.IO.Streams;


import Eos.Controllers.Serial;
import Eos.System.Core.Ticks;


export namespace eos {

	class SerialStream: public Stream {

		private:
			SerialDriver * const _drvSerial;
			Ticks _txTimeout;
			Ticks _rxTimeout;

		public:
			SerialStream(SerialDriver *drvSerial);

			void setWriteTimeout(Ticks timeout);
			void setReadTimeout(Ticks timeout);

			ResultU32 write(const uint8_t *buffer, size_t length) override;
			ResultU32 read(uint8_t *buffer, size_t bufferSize) override;
	};
}


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte i l'inicialitza.
/// \param    drvSerial: El driver del comunicacions serie.
///
eos::SerialStream::SerialStream(
	SerialDriver *drvSerial) :

	_drvSerial {drvSerial},
	_txTimeout {Ticks::infinite()},
	_rxTimeout {Ticks::infinite()} {
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el timeout d'escriptura.
/// \param    timeout: El valor.
///
void eos::SerialStream::setWriteTimeout(
	Ticks timeout) {

	_txTimeout = timeout;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el timeout de lectura.
/// \param    timeout: El valor.
///
void eos::SerialStream::setReadTimeout(
	Ticks timeout) {

	_rxTimeout = timeout;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el stream.
/// \param    buffer: El buffer de dades a escriure.
/// \param    length: El nombre de bytes a escriure.
/// \return   El nombre de bytes transmissos, i resultat de l'operacio.
//
eos::ResultU32 eos::SerialStream::write(
	const uint8_t *buffer,
	size_t length) {

	if ((buffer == nullptr) || (length == 0))
		return ResultU32::ErrorCodes::errorParameter;

	else if (_drvSerial == nullptr)
		return ResultU32::ErrorCodes::errorState;

	else {
		if (_drvSerial->transmit(buffer, length).is(SerialDriver::ErrorCode::busy))
			return ResultU32::ErrorCodes::busy;
		else {
			auto result = _drvSerial->wait(_txTimeout);
			if (result.isOk())
				return {ResultU32::ErrorCodes::ok, result.getValue()};
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
	size_t bufferSize) {

	if ((buffer == nullptr) || (bufferSize == 0))
		return ResultU32::ErrorCodes::errorParameter;

	if (_drvSerial == nullptr)
		return ResultU32::ErrorCodes::error;

	else {
		if (_drvSerial->receive(buffer, bufferSize).is(SerialDriver::ErrorCode::busy))
			return ResultU32::ErrorCodes::busy;
		else {
			auto result = _drvSerial->wait(_rxTimeout);
			if (result.isOk())
				return {ResultU32::ErrorCodes::ok, result.getValue()};
			else
				return ResultU32::ErrorCodes::timeout;
		}
	}
}
