#include "eos.h"
#include "appApplication.h"
#include "appLoopService.h"


using namespace eos;
using namespace app;


MyAppLoopService::MyAppLoopService(
	Application* application):

	AppLoopService(application) {

	MyApplication* app = static_cast<MyApplication*>(application);
	uartService = app->getUARTService();
}


void MyAppLoopService::onSetup() {

}


void MyAppLoopService::onLoop() {

	static uint8_t data[10];
	unsigned length;

	length = uartService->receive(data, sizeof(data), 500);
	if (length > 0)
		uartService->send(data, length, unsigned(-1));
}
