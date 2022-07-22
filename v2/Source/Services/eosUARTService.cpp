#include "eos.h"
#include "eosAssert.h"
#include "HTL/htlUART.h"
#include "Services/eosUARTService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    application: Aplicacio a la que afeigir el servei
/// \param    initParams: Parametres d'inicialitzacio.
///
UARTService::UARTService(
	Application *application,
	const Settings &settings):

	Service(application) {

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

	// Activa la interrupcio TXE, i comença la transmissio.
	//
	UART::enableInterrupt(UARTEvent::txEmpty);

	// Espera el final de la transmissio.
	//
	if (!_txPending.wait(blockTime)) {

		// Si ha pasat el temps de bloqueig i no ha acabat, aborta
		// la transmissio de dades
		//
		UART::disableInterrupt(UARTEvent::txEmpty);
		UART::disableInterrupt(UARTEvent::txComplete);
		UART::clearInterruptFlags(HAL_UART_EVENT_ALL);
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
	UART::enableInterrupt(UARTEvent::rxFull);

	if (!_rxPending.wait(blockTime)) {
		UART::disableInterrupt(UARTEvent::rxFull);
		UART::disableInterrupt(UARTEvent::pariry);
		UART::disableInterrupt(UARTEvent::error);
		UART::clearInterruptFlags(HAL_UART_EVENT_ALL);
    	_rxPending.release();
	}

	return _rxCount;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
///
void UARTService::onInitialize() {

	Service::onInitialize();

	UART::setInterruptFunction(uartInterruptFunction, this);
	UART::clearInterruptFlag(HAL_UART_EVENT_ALL);
}


/// ----------------------------------------------------------------------
/// \brief    Finalitzacio del servei.
///
void UARTService::onTerminate() {

	UART::setInterruptFunction(nullptr, nullptr);

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
	uint32_t event) {

	switch (event) {

		// RXNE (Reception data register not empty)
		//
		case HAL_UART_EVENT_RXFULL:
			_rxBuffer[_rxCount++] = UART::receive();
			if (_rxCount == _rxSize) {
				UART::disableInterrupt(HAL_UART_EVENT_RXFULL);
				UART::disableInterrupt(HAL_UART_EVENT_PARITY);
				UART::disableInterrupt(HAL_UART_EVENT_ERROR);
				_rxPending.releaseISR();
			}
			break;

		// TXE (Transmit data register empty)
		//
		case HAL_UART_EVENT_TXEMPTY: {
			if (_txCount == _txLength) {
				UART::disableInterrupt(HAL_UART_EVENT_TXEMPTY);
				UART::enableInterrupt(HAL_UART_EVENT_TXCOMPLETE);
			}
			else
				UART::send(_txBuffer[_txCount++]);
			break;
		}

		// Comprova un event TC (Transmit complete).
		//
		case HAL_UART_EVENT_TXCOMPLETE:
			UART::disableInterrupt(HAL_UART_EVENT_TXEMPTY);
			UART::disableInterrupt(HAL_UART_EVENT_TXCOMPLETE);
			_txPending.releaseISR();
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio de la UART.
/// \param    handler: Handler de la UART.
/// \param    params: Parametres.
/// \param    event: L'event que ha generat la interrupcio.
///
void UARTService::uartInterruptFunction(
	halUARTHandler handler,
	void* params,
	uint32_t event) {

	eosAssert(handler != nullptr);
	eosAssert(params != nullptr);

	UARTService *service = static_cast<UARTService*>(params);
	service->uartInterruptFunction(event);
}
