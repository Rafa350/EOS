#include "eos.h"
#include "Controllers/Serial/eosSlaveSerialDriver.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SlaveSerialDriver::SlaveSerialDriver():
    _state {State::reset},
    _txCompletedEvent {nullptr},
    _rxCompletedEvent {nullptr},
    _txCompletedEventEnabled {false},
    _rxCompletedEventEnabled {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SlaveSerialDriver::initialize() {

    if (_state == State::reset) {
        onInitialize();
        _state = State::ready;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SlaveSerialDriver::deinitialize() {

    if (_state == State::ready) {
        onDeinitialize();
        _state = State::reset;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicia l'escolta del master.
/// \param    txBuffer: El buffer de transmissio.
/// \param    txBufferSize: El tamany del buffer de transmissio.
/// \param    rxBuffer: El buffer de recepcio.
/// \param    rxBufferSize. el tamany del buffer de recepcio.
/// \return   True si tot es correcte.
///
bool SlaveSerialDriver::listen(
    const uint8_t *txBuffer,
    unsigned txBufferSize,
    uint8_t *rxBuffer,
    unsigned rxBufferSize) {

    if (_state == State::ready) {

        raiseListenStart();
        onListen(txBuffer, txBufferSize, rxBuffer, rxBufferSize);

        _state = State::listening;
    }

    return _state == State::listening;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'TxCompleted'
/// \param    event: L'event
/// \param    enabled: Indica si el deixa habilitat
///
void SlaveSerialDriver::setTxCompletedEvent(
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
void SlaveSerialDriver::setRxCompletedEvent(
    const IRxCompletedEvent &event,
    bool enabled) {

    _rxCompletedEvent = &event;
    _rxCompletedEventEnabled = enabled;
}


void SlaveSerialDriver::raiseListenStart() {

}


void SlaveSerialDriver::raiseTxCompleted(
    unsigned length) {

    if (_txCompletedEventEnabled) {

        TxCompletedEventArgs args = {
            .driver = this,
            .length = length
        };

        _txCompletedEvent->execute(args);
    }
}


void SlaveSerialDriver::raiseRxCompleted(
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
void SlaveSerialDriver::notifyTxCompleted(
    unsigned length) {

    if (_state == State::transmiting) {
        raiseTxCompleted(length);
        _state = State::ready;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Invoca a la funcio callback.
/// \param    length: Nombre de bytes rebuts
///
void SlaveSerialDriver::notifyRxCompleted(
    unsigned length) {

    if (_state == State::receiving) {
        raiseRxCompleted(length);
        _state = State::ready;
    }
}
