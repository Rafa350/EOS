module;


#include "eos.h"
#include "eosAssert.h"


export module Eos.System.IO.Streams.Serial;


export import Eos.System.IO.Streams;


import Eos.Result;
import Eos.Controllers.Serial;
import Eos.System.Core.Ticks;
import Eos.Types;


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

			StdResultU32 write(const UInt8 *buffer, UInt32 length) override;
			StdResultU32 read(UInt8 *buffer, UInt32 bufferSize) override;
	};
}


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte i l'inicialitza.
/// \param    drvSerial: El driver del comunicacions serie.
///
SerialStream::SerialStream(
	SerialDriver *drvSerial) :

	_drvSerial {drvSerial},
	_txTimeout {Ticks::infinite()},
	_rxTimeout {Ticks::infinite()} {
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el timeout d'escriptura.
/// \param    timeout: El valor.
///
void SerialStream::setWriteTimeout(
	Ticks timeout) {

	_txTimeout = timeout;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el timeout de lectura.
/// \param    timeout: El valor.
///
void SerialStream::setReadTimeout(
	Ticks timeout) {

	_rxTimeout = timeout;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el stream.
/// \param    buffer: El buffer de dades a escriure.
/// \param    length: El nombre de bytes a escriure.
/// \return   El nombre de bytes transmissos, i resultat de l'operacio.
//
StdResultU32 SerialStream::write(
	const UInt8 *buffer,
	UInt32 length) {

	if ((buffer == nullptr) || (length == 0))
		return StdErrorCode::errorParameter;

	else if (_drvSerial == nullptr)
		return StdErrorCode::errorState;

	else {
		if (_drvSerial->transmit(buffer, length).is(SerialDriver::ErrorCode::busy))
			return StdErrorCode::busy;
		else {
			auto result = _drvSerial->wait(_txTimeout);
			if (result.isOk())
				return {result.getValue()};
			else {
				_drvSerial->abort();
				return StdErrorCode::timeout;
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
StdResultU32 SerialStream::read(
	UInt8 *buffer,
	UInt32 bufferSize) {

	if ((buffer == nullptr) || (bufferSize == 0))
		return StdErrorCode::errorParameter;

	if (_drvSerial == nullptr)
		return StdErrorCode::error;

	else {
		if (_drvSerial->receive(buffer, bufferSize).is(SerialDriver::ErrorCode::busy))
			return StdErrorCode::busy;
		else {
			auto result = _drvSerial->wait(_rxTimeout);
			if (result.isOk())
				return {result.getValue()};
			else
				return StdErrorCode::timeout;
		}
	}
}
