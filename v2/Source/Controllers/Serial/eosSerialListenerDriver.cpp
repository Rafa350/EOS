#include "eos.h"
#include "Controllers/Serial/eosSerialListenerDriver.h"
#include "HTL/htl.h"


#ifdef HTL_ATOMIC
import htl.atomic;
#else
#include "HTL/htlAtomic.h"
#endif


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    txBuffer: Buffer de transmissio.
/// \param    txBufferSize: Tamany del buffer de transmissio.
/// \param    rxBuffer: Buffer de recepcio.
/// \param    rxBufferSize: Tamany de buffer de recepcio.
///
SerialListenerDriver::SerialListenerDriver(
	uint8_t *txBuffer,
	unsigned txBufferSize,
	uint8_t *rxBuffer,
	unsigned rxBufferSize) :

    _state {State::reset},
    _txBuffer {txBuffer, txBufferSize},
    _rxBuffer {rxBuffer, rxBufferSize} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SerialListenerDriver::initialize() {

    if (_state == State::reset) {
        onInitialize();
        _state = State::ready;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SerialListenerDriver::deinitialize() {

    if (_state == State::ready) {
        onDeinitialize();
        _state = State::reset;
    }
}

/// ----------------------------------------------------------------------
/// \brief    Transmissio de dades.
/// \param    buffer: Buffer.
/// \param    length: Contingut del buffer en bytes.
///
ResultU32 SerialListenerDriver::transmit(
	const uint8_t *buffer,
	unsigned length) {

	unsigned count = 0;

	if (_state == State::ready) {

		auto a = startAtomic();

		unsigned count = 0;
		while ((count < length) && _txBuffer.put(*buffer)) {
			buffer++;
			count++;
		}

		endAtomic(a);
	}

	return ResultU32(Results::success, count);
}


/// ----------------------------------------------------------------------
/// \brief    Recepcio de dades.
/// \param    buffer: Buffer.
/// \param    bufferSize: Tamany del buffer en bytes.
/// \param    timeout: Tamps maxim d'espera en ms.
/// \result   Resultat de l'operacio.
///
ResultU32 SerialListenerDriver::receive(
	uint8_t *buffer,
	unsigned bufferSize,
	unsigned timeout) {

	if (_state == State::ready) {

		if (_semRxBufferNotEmpty.wait(timeout)) {

			// Bloqueja interrupcions
			//
			auto a = startAtomic();

			// Llegeix les deades del buffer de recepcio i les transfereix
			// al buffer suministrat.
			//
			unsigned count = 0;
			while ((count < bufferSize) && _rxBuffer.get(*buffer)) {
				buffer++;
				count++;
			}

			// El resultat pot ser complert o parcial
			//
			auto result = _rxBuffer.isEmpty() ?
					Results::success : Results::pending;

			endAtomic(a);

			return ResultU32(result, count);
		}
		else
			return Results::timeout;
	}
	else
		return Results::busy;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el buffer de recepcio.
/// \param    pData: Punter a les dades les dades.
/// \param    size: Nombre de bytes de dades.
/// \param    irq: Indica si es crida des de una IRQ
/// \return   El nombre de bytes realment escrits.
/// \remarks  Cal controlar l'access simultani al buffer per part
///		      de les interrupcions.
///
unsigned SerialListenerDriver::rxBufferWrite(
	const uint8_t *pData,
	unsigned size,
	bool irq) {

	bool startEmpty = _rxBuffer.isEmpty();

	unsigned count = 0;
	while ((count < size) && _rxBuffer.put(*pData)) {
		count++;
		pData++;
	}

	// Notifica si el buffer no esta buit, pero nomes si al
	// principi ho era.
	//
	if (startEmpty && (count > 0)) {
		_semRxBufferNotEmpty.releaseISR();
		raiseRxBufferNotEmpty();
	}

	return count;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix el buffer de transmissio.
/// \param    pData: Punter a les dades.
/// \param    size: Nombre maxim de bytes a lleigit.
/// \param    irq: Indica si es crida desde una IRQ
/// \return   El nombre de bytes realment lleigits.
/// \remarks  Cal controlar l'access simultani al buffer per part
///		      de les interrupcions.
///
unsigned SerialListenerDriver::txBufferRead(
	uint8_t *pData,
	unsigned size,
	bool irq) {

	unsigned count = 0;

	while ((count < size) && _txBuffer.get(*pData)) {
		pData++;
		count++;
	}

	return count;
}


/// ----------------------------------------------------------------------
/// \brief    Genera el event de notificacio 'txBufferEmpty'
///
void SerialListenerDriver::raiseTxBufferEmpty() {

	_notifyEventRaiser.raise(NotifyID::txBufferEmpty, nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Genera el event de notificacio 'rxBufferNotEmpty'
///
void SerialListenerDriver::raiseRxBufferNotEmpty() {

	_notifyEventRaiser.raise(NotifyID::rxBufferNotEmpty, nullptr);
}
