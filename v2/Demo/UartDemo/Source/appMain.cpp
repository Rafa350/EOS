#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halINT.h"
#include "HAL/halUART.h"

#include "appApplication.h"

#include "string.h"
#include "stdio.h"


using namespace eos;
using namespace app;


UARTData uart6Data;


/// ----------------------------------------------------------------------
/// \brief Entrada al programa.
///
void appMain() {
#if 0
	// Inicialitza els port utilitzats per la UART
	//
	GPIOInitializePinInfo gpioInfo;
	gpioInfo.options = HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_HIGH | HAL_GPIO_PULL_UP;
	gpioInfo.alt = HAL_GPIO_AF8_USART6;

	// Pin TX
	gpioInfo.port = HAL_GPIO_PORT_C;
	gpioInfo.pin = HAL_GPIO_PIN_6;
	halGPIOInitializePins(&gpioInfo, 1);

	// Pin RX
	gpioInfo.port = HAL_GPIO_PORT_C;
	gpioInfo.pin = HAL_GPIO_PIN_7;
	halGPIOInitializePins(&gpioInfo, 1);

	// Inicialitza la UART
	//
	UARTInitializeInfo uartInfo;

	uartInfo.channel = HAL_UART_CHANNEL_6;
	uartInfo.options =
		HAL_UART_CLOCK_AUTO | HAL_UART_BAUD_9600 | HAL_UART_OVERSAMPLING_16 |
		HAL_UART_LEN_8 | HAL_UART_STOP_10 | HAL_UART_PARITY_NONE;

	UARTHandler hUart = halUARTInitialize(&uart6Data, &uartInfo);

	//halINTEnableInterruptVector(HAL_INT_VECTOR_UART6);

	// Envia dades de test
	//
	const char* greetings = "Hello world!\r\n";
	char buffer[100];

	for (int i = 0; i < 1; i++) {
		sprintf(buffer, "%d, %s", i, greetings);
		halUARTTransmit(hUart, (uint8_t*) buffer, strlen(buffer));
	}

	HAL_Delay(2000);

	// Desinicialitza la UART
	//
	halUARTDeinitialize(hUart);
#endif

	Application* app = new MyApplication();
    app->run();
    delete app;
}
