#include "eos.h"
#include "eosAssert.h"
#include "HAL/halUART.h"
#include "Services/eosUARTService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    application: Aplicacio a la que afeigir el servei
/// \param    initParams: Parametres d'inicialitzacio.
///
UARTService::UARTService(
	Application* application,
	const Settings& settings):

	Service(application),
	_uart(settings.hUART) {

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
	uint8_t* data,
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
	_uart.enableInterrupts(HAL_UART_EVENT_TXEMPTY);

	// Espera el final de la transmissio.
	//
	if (!_txPending.wait(blockTime)) {

		// Si ha pasat el temps de bloqueig i no ha acabat, aborta
		// la transmissio de dades
		//
		_uart.disableInterrupts(HAL_UART_EVENT_TXEMPTY);
		_uart.disableInterrupts(HAL_UART_EVENT_TXCOMPLETE);
		_uart.clearInterruptFlags(HAL_UART_EVENT_ALL);
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
	_uart.enableInterrupts(HAL_UART_EVENT_RXFULL);

	if (!_rxPending.wait(blockTime)) {
		_uart.disableInterrupts(HAL_UART_EVENT_RXFULL);
		_uart.disableInterrupts(HAL_UART_EVENT_PARITY);
		_uart.disableInterrupts(HAL_UART_EVENT_ERROR);
		_uart.clearInterruptFlags(HAL_UART_EVENT_ALL);
    	_rxPending.release();
	}

	return _rxCount;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
///
void UARTService::onInitialize() {

	Service::onInitialize();

	halUARTSetInterruptFunction(_uart, uartInterruptFunction, this);
	halUARTClearInterruptFlags(_uart, HAL_UART_EVENT_ALL);
}


/// ----------------------------------------------------------------------
/// \brief    Finalitzacio del servei.
///
void UARTService::onTerminate() {

	halUARTSetInterruptFunction(_uart, nullptr, nullptr);

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
			_rxBuffer[_rxCount++] = _uart.receive();
			if (_rxCount == _rxSize) {
				_uart.disableInterrupts(HAL_UART_EVENT_RXFULL);
				_uart.disableInterrupts(HAL_UART_EVENT_PARITY);
				_uart.disableInterrupts(HAL_UART_EVENT_ERROR);
				_rxPending.releaseISR();
			}
			break;

		// TXE (Transmit data register empty)
		//
		case HAL_UART_EVENT_TXEMPTY: {
			if (_txCount == _txLength) {
				_uart.disableInterrupts(HAL_UART_EVENT_TXEMPTY);
				_uart.enableInterrupts(HAL_UART_EVENT_TXCOMPLETE);
			}
			else
				_uart.send(_txBuffer[_txCount++]);
			break;
		}

		// Comprova un event TC (Transmit complete).
		//
		case HAL_UART_EVENT_TXCOMPLETE:
			_uart.disableInterrupts(HAL_UART_EVENT_TXEMPTY);
			_uart.disableInterrupts(HAL_UART_EVENT_TXCOMPLETE);
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

	UARTService* service = static_cast<UARTService*>(params);
	service->uartInterruptFunction(event);
}
