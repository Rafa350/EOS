#include "eos.h"
#include "Controllers/Serial/eosSerialDriverBase.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SerialDriverBase::SerialDriverBase() :

	_txCompletedEvent {nullptr},
	_rxCompletedEvent {nullptr},
	_abortedEvent {nullptr},
	_txCompletedEventEnabled {false},
	_rxCompletedEventEnabled {false},
	_abortedEventEnabled {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void SerialDriverBase::initialize() {

	initializeImpl();
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitza el driver.
///
void SerialDriverBase::deinitialize() {

	deinitializeImpl();
    
	_txCompletedEvent = nullptr;
	_rxCompletedEvent = nullptr;
	_abortedEvent = nullptr;
	_txCompletedEventEnabled = false;
	_rxCompletedEventEnabled = false;
	_abortedEventEnabled = false;
}



/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'TxCompleted'
/// \param    event: L'event
/// \param    enabled: Indica si el deixa habilitat
///
void SerialDriverBase::setTxCompletedEvent(
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
void SerialDriverBase::setRxCompletedEvent(
	const IRxCompletedEvent &event,
	bool enabled) {

	_rxCompletedEvent = &event;
	_rxCompletedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de transmissio.
/// \param    length: Nombre de bytes transmessos.
///
void SerialDriverBase::notifyTxCompleted(
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
/// \brief    Invoca a la funcio callback.
/// \param    length: Nombre de bytes rebuts
///
void SerialDriverBase::notifyRxCompleted(
	unsigned length) {

	if (_rxCompletedEventEnabled) {

		RxCompletedEventArgs args = {
		    .driver = this,
		    .length = length
		};

		_rxCompletedEvent->execute(args);
	}
}
