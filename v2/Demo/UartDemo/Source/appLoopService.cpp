#include "eos.h"
#include "htl/htlUART.h"
#include "appApplication.h"
#include "appLoopService.h"


using namespace eos;
using namespace htl;
using namespace app;


MyAppLoopService::MyAppLoopService(
	Application* application):

	AppLoopService(application),
	_serial(nullptr),
	_txCompletedCallback(*this, &MyAppLoopService::txCompletedEventHandler),
	_rxCompletedCallback(*this, &MyAppLoopService::rxCompletedEventHandler) {

}


void MyAppLoopService::onSetup() {

	_serial = new SerialDriver_IT(getUARTAdapter<config::uartService::UART>());
	_serial->initialize();
	_serial->setTxCompletedCallback(_txCompletedCallback);
	_serial->setRxCompletedCallback(_rxCompletedCallback);
}


void MyAppLoopService::onLoop() {

	uint8_t buffer[10];

	while (true) {

		if (_serial->receive(buffer, sizeof(buffer))) {
			if (_rxCompleted.wait(unsigned(-1))) {
				if (_rxDataCount > 0) {
					if (_serial->transmit(buffer, _rxDataCount))
						_txCompleted.wait(unsigned(-1));
				}
			}
		}
	}
}

void MyAppLoopService::txCompletedEventHandler(
	const SerialDriver_IT::TxCompletedEventArgs &args) {

	_txCompleted.releaseISR();
}


void MyAppLoopService::rxCompletedEventHandler(
	const SerialDriver_IT::RxCompletedEventArgs &args) {

	_rxDataCount = args.count;
	_rxCompleted.releaseISR();
}

