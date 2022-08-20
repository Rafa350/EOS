#include "eos.h"
#include "appApplication.h"
#include "appLoopService.h"


using namespace eos;
using namespace app;


MyAppLoopService::MyAppLoopService(
	Application* application,
	UARTService *uartService):

	AppLoopService(application),
	_uartService(uartService) {

}


void MyAppLoopService::onSetup() {

}


void MyAppLoopService::onLoop() {

	/*char ch;

	if ((ch = getChar()) != 0) {
		putChar(ch);
	}*/
}


char MyAppLoopService::getChar() {

	char ch;
	if (_uartService->receive((uint8_t*) &ch, sizeof(ch), unsigned(-1)))
		return ch;
	else
		return 0;
}


void MyAppLoopService::putChar(
	char ch) {

	_uartService->send((uint8_t*) &ch, sizeof(ch), unsigned(-1));
}


void MyAppLoopService::putString(char *s) {

	_uartService->send((uint8_t*) s, strlen(s), unsigned(-1));
}
