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
/// \return   True si l'operacio finalitza correctament.
///
bool UARTService::send(
	uint8_t* data,
	unsigned length,
	unsigned blockTime) {

	Command cmd;
	cmd.data = data;
	cmd.length = length;
	return commandQueue.push(cmd,  unsigned(-1));
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

	Command cmd;
	if (commandQueue.pop(cmd,  unsigned(-1))) {

		// Inicia la comunicacio
		//
		txData = cmd.data;
		txLength = cmd.length;
		txCount = 0;
		halUARTEnableInterrupts(hUART, HAL_UART_EVENT_TXE);

		// Espera que finalitzi la comunicacio pendent.
		//
		txPending.wait(-1);
	}
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
		if (txCount == txLength) {
			halUARTDisableInterrupts(hUART, HAL_UART_EVENT_TXE);
			halUARTEnableInterrupts(hUART, HAL_UART_EVENT_TC);
		}
		else
			halUARTSend(hUART, txData[txCount++]);
	}

	// Comprova un event TC (Transmit complete).
	//
	if (event == HAL_UART_EVENT_TC) {
		halUARTDisableInterrupts(hUART, HAL_UART_EVENT_ALL);
		txPending.releaseISR();
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
