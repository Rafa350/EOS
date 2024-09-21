#include "eos.h"
#include "eosAssert.h"
#include "System/IO/eosSerialStream.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte.
///
SerialStream::SerialStream() :

	_drvSerial {nullptr},
	_txCompletedEvent {*this, &SerialStream::txCompletedEventHandler},
	_rxCompletedEvent {*this, &SerialStream::rxCompletedEventHandler} {
}


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte i l'inicialitza.
/// \param    drvSerial: El driver del comunicacions serie.
///
SerialStream::SerialStream(
	SerialDriver *drvSerial) :

	_drvSerial {nullptr},
	_txCompletedEvent {*this, &SerialStream::txCompletedEventHandler},
	_rxCompletedEvent {*this, &SerialStream::rxCompletedEventHandler} {

	initialize(drvSerial);
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa l'event 'txCompleted'
/// \params   : args : Parametres del event.
///
void SerialStream::txCompletedEventHandler(
	const SerialDriver::TxCompletedEventArgs &args) {

	_txCompleted.releaseISR();
}


/// ----------------------------------------------------------------------
/// \brief    : Procesa l'event 'rxCompleted'
/// \params   : args : Parametres del event.
///
void SerialStream::rxCompletedEventHandler(
	const SerialDriver::RxCompletedEventArgs &args) {

	_rxDataCount = args.length;
	_rxCompleted.releaseISR();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el stream.
/// \param    drvSerial:: El driver del canal serie.
/// \return   El resultat de l'operacio.
///
Stream::Result SerialStream::initialize(
	SerialDriver *drvSerial) {

	eosAssert(drvSerial != nullptr);
	eosAssert(_drvSerial == nullptr);

	if (_drvSerial == nullptr) {
		_drvSerial = drvSerial;
		_drvSerial->initialize();
		_drvSerial->setTxCompletedEvent(_txCompletedEvent);
		_drvSerial->setRxCompletedEvent(_rxCompletedEvent);
		return Result::success();
	}
	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Deinicialitza el stream.
/// \return   El resultat de l'operacio.
///
Stream::Result SerialStream::deinitialize() {

	if (_drvSerial != nullptr) {
		_drvSerial->deinitialize();
		_drvSerial = nullptr;
		return Result::success();
	}
	else
		return Result::error();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el stream.
/// \param    data: El bloc de dades a escriure.
/// \param    length: El nombre de bytes a escriure.
/// \param    count: El nombre de bytes escrits.
/// \return   El resultat de l'operacio.
//
Stream::Result SerialStream::write(
	const uint8_t *data,
	unsigned length,
	unsigned *count) {

	if (_drvSerial == nullptr)
		return Result::error();

	else {
		_drvSerial->transmit(data, length);
		if (_txCompleted.wait(unsigned(-1))) {

			if (count != nullptr)
				*count = length;

			return Result::success();
		}
		else
			return Result::timeout();
	}
}


/// ---------------------------------------------------------------------
/// \brief    Llegeix dades des del stream.
/// \param    data: Bloc on deixar les dades.
/// \param    size: Tamany del bloc en bytes.
/// \param    count: El nombre de bytes lleigits.
/// \return   El resultat de l'operacio.
///
Stream::Result SerialStream::read(
	uint8_t *data,
	unsigned size,
	unsigned *count) {

	if (_drvSerial == nullptr)
		return Result::error();

	else {
		_drvSerial->receive(data, size);

		if (_rxCompleted.wait(unsigned(-1))) {

			if (count != nullptr)
				*count = _rxDataCount;

			return Result::success();
		}
		else
			return Result::timeout();
	}
}
