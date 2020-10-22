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
	const InitParams& initParams):

	Service(application),
	hUART(initParams.hUART) {

	rxPending.release();
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
	txBuffer = data;
	txLength = length;
	txCount = 0;

	// Activa la interrupcio TXE, i comença la transmissio.
	//
	halUARTEnableInterrupts(hUART, HAL_UART_EVENT_TXEMPTY);

	// Espera el final de la transmissio.
	//
	if (!txPending.wait(blockTime)) {

		// Si ha pasat el temps de bloqueig i no ha acabat, aborta
		// la transmissio de dades
		//
		halUARTDisableInterrupts(hUART, HAL_UART_EVENT_TXEMPTY);
		halUARTDisableInterrupts(hUART, HAL_UART_EVENT_TXCOMPLETE);
		halUARTClearInterruptFlags(hUART, HAL_UART_EVENT_ALL);
	}

	return txCount;
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

	rxBuffer = data;
	rxSize = size;
	rxCount = 0;

	// Activa la interrupcio RXNE. A partir d'aquest moment,
	// cada cop que el registre de recepcio no estigui buit,
	// es genera una interrupcio.
	//
	halUARTEnableInterrupts(hUART, HAL_UART_EVENT_RXFULL);

	if (!rxPending.wait(blockTime)) {
    	halUARTDisableInterrupts(hUART, HAL_UART_EVENT_RXFULL);
		halUARTDisableInterrupts(hUART, HAL_UART_EVENT_PARITY);
		halUARTDisableInterrupts(hUART, HAL_UART_EVENT_ERROR);
		halUARTClearInterruptFlags(hUART, HAL_UART_EVENT_ALL);
    	rxPending.release();
	}

	return rxCount;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio del servei.
///
void UARTService::onInitialize() {

	Service::onInitialize();

	halUARTSetInterruptFunction(hUART, uartInterruptFunction, this);
	halUARTClearInterruptFlags(hUART, HAL_UART_EVENT_ALL);
}


/// ----------------------------------------------------------------------
/// \brief    Finalitzacio del servei.
///
void UARTService::onTerminate() {

	halUARTSetInterruptFunction(hUART, nullptr, nullptr);

	Service::onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Tasca del servei.
///
void UARTService::onTask() {

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
			rxBuffer[rxCount++] = halUARTReceive(hUART);
			if (rxCount == rxSize) {
				halUARTDisableInterrupts(hUART, HAL_UART_EVENT_RXFULL);
				halUARTDisableInterrupts(hUART, HAL_UART_EVENT_PARITY);
				halUARTDisableInterrupts(hUART, HAL_UART_EVENT_ERROR);
				rxPending.releaseISR();
			}
			break;

		// TXE (Transmit data register empty)
		//
		case HAL_UART_EVENT_TXEMPTY: {
			if (txCount == txLength) {
				halUARTDisableInterrupts(hUART, HAL_UART_EVENT_TXEMPTY);
				halUARTEnableInterrupts(hUART, HAL_UART_EVENT_TXCOMPLETE);
			}
			else
				halUARTSend(hUART, txBuffer[txCount++]);
			break;
		}

		// Comprova un event TC (Transmit complete).
		//
		case HAL_UART_EVENT_TXCOMPLETE:
			halUARTDisableInterrupts(hUART, HAL_UART_EVENT_TXEMPTY);
			halUARTDisableInterrupts(hUART, HAL_UART_EVENT_TXCOMPLETE);
			txPending.releaseISR();
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
	UARTHandler handler,
	void* params,
	uint32_t event) {

	eosAssert(handler != nullptr);
	eosAssert(params != nullptr);

	UARTService* service = static_cast<UARTService*>(params);
	service->uartInterruptFunction(event);
}
