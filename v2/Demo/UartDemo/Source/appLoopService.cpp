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

	char ch;

	if ((ch = getChar()) != 0) {
		putChar(ch);
	}
}


char MyAppLoopService::getChar() {

	char ch;
	if (uartService->receive((uint8_t*) &ch, sizeof(ch), unsigned(-1)))
		return ch;
	else
		return 0;
}


void MyAppLoopService::putChar(
	char ch) {

	uartService->send((uint8_t*) &ch, sizeof(ch), unsigned(-1));
}


void MyAppLoopService::putString(char *s) {

	uartService->send((uint8_t*) s, strlen(s), unsigned(-1));
}
