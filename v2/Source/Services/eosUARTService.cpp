#include "eos.h"
#include "eosAssert.h"
#include "HAL/halUART.h"
#include "Services/eosUARTService.h"

#include "string.h"

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
	hUART(initParams.hUART),
	commandQueue(10) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor de l'objecte.
///
UARTService::~UARTService() {

}


/// ----------------------------------------------------------------------
/// \brief    Transmeteix un bloc de dades.
/// \param    data: El bloc de dades.
/// \param    length: Longitut en bytes del bloc de dades.
/// \params   blockTime: Tempos maxim de bloqueig.
///
void UARTService::send(
	uint8_t* data,
	unsigned length,
	unsigned blockTime) {

	Command cmd;
	cmd.data = data;
	cmd.length = length;
	commandQueue.push(cmd, blockTime);
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

	static char* text = "cagarro pudent.\r\n";

	halUARTTransmitINT(hUART, (uint8_t*) text, strlen(text));

	// Espera que finalitzi la comunicacio pendent.
	///
	semaphore.wait(-1);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio de la UART.
/// \param    event: L'event que ha generat la interrupcio.
///
void UARTService::uartInterruptFunction(
	uint32_t event) {

	// Comprova si es un event TXE (Transmit data register empty)
	//
	if (event == HAL_UART_EVENT_TXE) {

	}

	// Comprova un event TC (Transmit complete).
	//
	if (event == HAL_UART_EVENT_TC) {
		semaphore.releaseISR();
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

	UARTService* service = static_cast<UARTService*>(params);
	service->uartInterruptFunction(event);
}
