#include "eos.h"
#include "Controllers/Serial/eosSerialDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SerialDriver::SerialDriver() :
    _state {State::reset},
	_txCompletedEvent {nullptr},
	_rxCompletedEvent {nullptr},
	_txCompletedEventEnabled {false},
	_rxCompletedEventEnabled {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SerialDriver::initialize() {

    if (_state == State::reset) {

        onInitialize();

        _state = State::ready;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SerialDriver::deinitialize() {

    if (_state == State::ready) {

        onDeinitialize();

        _txCompletedEvent = nullptr;
        _rxCompletedEvent = nullptr;
        _txCompletedEventEnabled = false;
        _rxCompletedEventEnabled = false;

        _state = State::reset;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicia una transmissio d'un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    length: Nombre de bytes en el buffer.
/// \return   True si tot es correcte.
///
bool SerialDriver::transmit(
    const uint8_t *buffer,
    unsigned length) {

    if (_state == State::ready) {
        onTransmit(buffer, length);
        _state = State::transmiting;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la recepcio d'un bloc de dades.
/// \param    buffer: El buffer de dades.
/// \param    bufferSize: El tamany del buffer en bytes.
/// \return   True si tot es correcte.
///
bool SerialDriver::receive(
    uint8_t *buffer,
    unsigned bufferSize) {

    if (_state == State::ready) {
        onReceive(buffer, bufferSize);
        _state = State::receiving;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'TxCompleted'
/// \param    event: L'event
/// \param    enabled: Indica si el deixa habilitat
///
void SerialDriver::setTxCompletedEvent(
	const ITxCompletedEvent &event,
	bool enabled) {

	_txCompletedEvent = &event;
	_txCompletedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'RxCompleted'
/// \param    event: L'event
/// \param    enabled: Indica si el deixa habilitat
///
void SerialDriver::setRxCompletedEvent(
	const IRxCompletedEvent &event,
	bool enabled) {

	_rxCompletedEvent = &event;
	_rxCompletedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Genera el event 'TxCompleted'.
///
void SerialDriver::raiseTxCompleted(
    unsigned length) {

    if (_txCompletedEventEnabled) {

        TxCompletedEventArgs args = {
            .driver = this,
            .length = length
        };

        _txCompletedEvent->execute(args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Genera l'event 'RxCompleted'.
///
void SerialDriver::raiseRxCompleted(
    unsigned length) {

    if (_rxCompletedEventEnabled) {

        RxCompletedEventArgs args = {
            .driver = this,
            .length = length
        };

        _rxCompletedEvent->execute(args);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de transmissio.
/// \param    length: Nombre de bytes transmessos.
///
void SerialDriver::notifyTxCompleted(
	unsigned length) {

    if (_state == State::transmiting) {
        raiseTxCompleted(length);
        _state = State::ready;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de la recepcio.
/// \param    length: Nombre de bytes rebuts
///
void SerialDriver::notifyRxCompleted(
	unsigned length) {

    if (_state == State::receiving) {
        raiseRxCompleted(length);
        _state = State::ready;
    }
}
