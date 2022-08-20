#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlUART.h"
#include "Services/eosUARTService.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    application: Aplicacio a la que afeigir el servei
/// \param    initParams: Parametres d'inicialitzacio.
///
UARTService::UARTService(
	Application *application):

	Service(application),
	_uart(htl::getUARTAdapter<config::uartService::UART>()) {

	_rxPending.release();
}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
UARTService::~UARTService() {

}


/// ----------------------------------------------------------------------
/// \brief    Transmet un bloc de dades.
/// \param    data: Buffer de dades.
/// \param    length: Nombre de bytes en el buffer.
/// \params   blockTime: Temps maxim de bloqueig.
/// \return   Nombre de bytes transmessos realment.
/// \remarks  Si no es pot transmetre en el temps 'blockTime', es cancel·la
///           la transmissio dels bytes que resten.
///
unsigned UARTService::send(
	uint8_t *data,
	unsigned length,
	unsigned blockTime) {

	eosAssert(data != nullptr);
	eosAssert(length > 0);

	// Inicialitza les variables per la transmissio
	//
	_txBuffer = data;
	_txLength = length;
	_txCount = 0;

	// Activa la interrupcio TXE, i comença la transmissio. Cada cop
	// que el registre de transmissio estigui buit, es genera una interrupcio.
	//
	_uart.enableInterrupt(UARTEvent::txEmpty);

	// Espera el final de la transmissio.
	//
	if (!_txPending.wait(blockTime)) {

		// Si ha pasat el temps de bloqueig i no ha acabat, aborta
		// la transmissio de dades
		//
		_uart.disableInterrupt(UARTEvent::txEmpty);
		_uart.disableInterrupt(UARTEvent::txComplete);
		_uart.clearInterruptFlags();
	}

	return _txCount;
}


/// ----------------------------------------------------------------------
/// \brief    Reb un bloc de dades.
/// \param    data: El buffer de dades.
/// \param    size: Tamany del buffer.
/// \param    blockTime: Temps maxim de bloqueig.
/// \return   El nombre de bytes rebuts.
///
unsigned UARTService::receive(
	uint8_t* data,
	unsigned size,
	unsigned blockTime) {

	eosAssert(data != nullptr);
	eosAssert(size > 0);

	_rxBuffer = data;
	_rxSize = size;
	_rxCount = 0;

	// Activa la interrupcio RXNE. A partir d'aquest moment,
	// cada cop que el registre de recepcio no estigui buit,
	// es genera una interrupcio.
	//
	_uart.enableInterrupt(UARTEvent::rxNotEmpty);

	if (!_rxPending.wait(blockTime)) {
		_uart.disableInterrupt(UARTEvent::rxNotEmpty);
		_uart.disableInterrupt(UARTEvent::parity);
		_uart.disableInterrupt(UARTEvent::framming);
		_uart.disableInterrupt(UARTEvent::overrun);
		_uart.disableInterrupt(UARTEvent::noise);
		_uart.clearInterruptFlags();
    	_rxPending.release();
	}

	return _rxCount;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
///
void UARTService::onInitialize() {

	Service::onInitialize();

	_uart.setInterruptFunction(uartInterruptFunction, this);
	_uart.clearInterruptFlags();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitzacio del servei.
///
void UARTService::onTerminate() {

	_uart.setInterruptFunction(nullptr, nullptr);

	Service::onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Tasca del servei.
/// \param    task: L'objecte Task que executa el servei.
///
void UARTService::onTask(
	Task *task) {

	Task::delay(1000);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio de la UART.
/// \param    event: L'event que ha generat la interrupcio.
///
void UARTService::uartInterruptFunction(
	UARTEvent event) {

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wswitch"
	#pragma GCC diagnostic ignored "-Wswitch-default"
	switch (event) {

		// RXNE (Reception data register not empty)
		//
		case UARTEvent::rxNotEmpty:
			_rxBuffer[_rxCount++] = _uart.read();
			if (_rxCount == _rxSize) {
				_uart.disableInterrupt(UARTEvent::rxNotEmpty);
				_uart.disableInterrupt(UARTEvent::parity);
				_uart.disableInterrupt(UARTEvent::framming);
				_uart.disableInterrupt(UARTEvent::overrun);
				_uart.disableInterrupt(UARTEvent::noise);
				_rxPending.releaseISR();
			}
			break;

		// TXE (Transmit data register empty)
		//
		case UARTEvent::txEmpty: {
			if (_txCount == _txLength) {
				_uart.disableInterrupt(UARTEvent::txEmpty);
				_uart.enableInterrupt(UARTEvent::txComplete);
			}
			else
				_uart.write(_txBuffer[_txCount++]);
			break;
		}

		// Comprova un event TC (Transmit complete).
		//
		case UARTEvent::txComplete:
			_uart.disableInterrupt(UARTEvent::txEmpty);
			_uart.disableInterrupt(UARTEvent::txComplete);
			_txPending.releaseISR();
			break;
	}
	#pragma GCC diagnostic pop
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio de la UART.
/// \param    handler: Handler de la UART.
/// \param    params: Parametres.
/// \param    event: L'event que ha generat la interrupcio.
///
void UARTService::uartInterruptFunction(
	UARTEvent event,
	UARTInterruptParam param) {

	UARTService *service = static_cast<UARTService*>(param);
	service->uartInterruptFunction(event);
}
