module;

#include "eos.h"
#include "eosAssert.h"
#include "eosTime.h"
#include "eosResults.h"
#include "Controllers/Serial/eosSerialDriver.h"
#include "System/IO/eosStream.h"


export module Eos.IO.SerialStream;


export namespace eos {

	class SerialStream: public Stream {

		private:
			SerialDriver * const _drvSerial;
			Time _txTimeout = Times::infinite;
			Time _rxTimeout = Times::infinite;

		public:
			SerialStream(SerialDriver *drvSerial);

			void setWriteTimeout(Time timeout);
			void setReadTimeout(Time timeout);

			ResultU32 write(const uint8_t *buffer, uint32_t length) override;
			ResultU32 read(uint8_t *buffer, uint32_t bufferSize) override;
	};
}



/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte i l'inicialitza.
/// \param    drvSerial: El driver del comunicacions serie.
///
eos::SerialStream::SerialStream(
	SerialDriver *drvSerial) :

	_drvSerial {drvSerial} {
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el timeout d'escriptura.
/// \param    timeout: El valor.
///
inline void eos::SerialStream::setWriteTimeout(
	Time timeout) {

	_txTimeout = timeout;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el timeout de lectura.
/// \param    timeout: El valor.
///
inline void eos::SerialStream::setReadTimeout(
	Time timeout) {

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
