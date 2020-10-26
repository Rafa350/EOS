#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halINT.h"
#include "HAL/halSYS.h"
#ifdef EOS_PIC32
#include "HAL/PIC32/halCN.h"
#endif
#include "HAL/halTMR.h"
#include "HAL/halUART.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "System/eosApplication.h"

#include "appApplication.h"
#include "appLoopService.h"


using namespace eos;
using namespace app;


TMRData digInputTimerData;   // Dades del TMR del servei DigInputService
TMRData digOutputTimerData;  // Dades del TMR del servei DigOutputService
UARTData uartData;           // Dades de la UART del servei UARTService


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication():
    sw1EventCallback(this, &MyApplication::sw1EventHandler)
#ifdef EXIST_SWITCHES_SW2
    , sw2EventCallback(this, &MyApplication::sw2EventHandler)
#endif
#ifdef EXIST_SWITCHES_SW3
    , sw3EventCallback(this, &MyApplication::sw3EventHandler)
#endif
{

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

	initializeHardware();
	initializeServices();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el hardware associat a l'aplicacio.
///
void MyApplication::initializeHardware() {

	GPIOPinSettings gpioSettings;
	UARTSettings uartSettings;
	TMRSettings tmrSettings;

	// Inicialitza els pins SW1, SW2 i SW3 dels pulsadors
	//
	gpioSettings.options = HAL_GPIO_MODE_INPUT;
	gpioSettings.alt = HAL_GPIO_AF_NONE;

#ifdef EXIST_SWITCHES_SW1
	gpioSettings.port = SWITCHES_SW1_PORT;
	gpioSettings.pin = SWITCHES_SW1_PIN;
    halGPIOInitializePins(&gpioSettings, 1);
#ifdef EOS_PIC32
    halCNInitializeLine(SWITCHES_SW1_CN, HAL_CN_PULL_UP);
#endif
#endif

#ifdef EXIST_SWITCHES_SW2
	gpioSettings.port = SWITCHES_SW2_PORT;
	gpioSettings.pin = SWITCHES_SW2_PIN;
    halGPIOInitializePins(&gpioSettings, 1);
    halCNInitializeLine(SWITCHES_SW2_CN, HAL_CN_PULL_UP);
#endif

#ifdef EXIST_SWITCHES_SW3
	gpioSettings.port = SWITCHES_SW3_PORT;
	gpioSettings.pin = SWITCHES_SW3_PIN;
    halGPIOInitializePins(&gpioSettings, 1);
    halCNInitializeLine(SWITCHES_SW3_CN, HAL_CN_PULL_UP);
#endif

    // Inicialitza els pins LED1, LED2 i LED3 dels leds
    //
    gpioSettings.options = HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR;
    gpioSettings.alt = HAL_GPIO_AF_NONE;

#ifdef EXIST_LEDS_LED1
    gpioSettings.port = LEDS_LED1_PORT;
    gpioSettings.pin = LEDS_LED1_PIN;
    halGPIOInitializePins(&gpioSettings, 1);
#endif

#ifdef EXIST_LEDS_LED2
    gpioSettings.port = LEDS_LED2_PORT;
    gpioSettings.pin = LEDS_LED2_PIN;
    halGPIOInitializePins(&gpioSettings, 1);
#endif

#ifdef EXIST_LEDS_LED3
    gpioSettings.port = LEDS_LED3_PORT;
    gpioSettings.pin = LEDS_LED3_PIN;
    halGPIOInitializePins(&gpioSettings, 1);
#endif

    // Inicialitza els pins TX/RX de la UART
	//
	gpioSettings.options = HAL_GPIO_MODE_ALT_PP | HAL_GPIO_SPEED_HIGH | HAL_GPIO_PULL_UP;
	gpioSettings.alt = HAL_GPIO_AF8_USART6;

	gpioSettings.port = HAL_GPIO_PORT_C;
	gpioSettings.pin = HAL_GPIO_PIN_6;
	halGPIOInitializePins(&gpioSettings, 1);

	gpioSettings.port = HAL_GPIO_PORT_C;
	gpioSettings.pin = HAL_GPIO_PIN_7;
	halGPIOInitializePins(&gpioSettings, 1);

	// Inicialitza UART6
	//
	uartSettings.channel = HAL_UART_CHANNEL_6;
	uartSettings.options =
		HAL_UART_CLOCK_AUTO | HAL_UART_BAUD_9600 | HAL_UART_OVERSAMPLING_16 |
		HAL_UART_LEN_8 | HAL_UART_STOP_1 | HAL_UART_PARITY_NONE;
	halUARTInitialize(&uartData, &uartSettings);
	halINTEnableInterruptVector(HAL_INT_VECTOR_UART6);
	halINTSetInterruptVectorPriority(HAL_INT_VECTOR_UART6, HAL_INT_PRIORITY_10, HAL_INT_SUBPRIORITY_0);

	// Inicialitza el temporitzador per les entrades digitals
	//
	tmrSettings.timer = DigInputService_Timer;
#if defined(EOS_PIC32)
    tmrSettings.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_64;
    tmrSettings.period = ((halSYSGetPeripheralClockFrequency() * DigInputService_TimerPeriod) / 64000) - 1;
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
    tmrSettings.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_1;
    tmrSettings.prescaler = (halSYSGetTimerClock1Frequency() / 1000000L) - 1; // 1MHz
    tmrSettings.period = (1000 * DigInputService_TimerPeriod) - 1;
#else
    #error CPU no soportada
#endif
    halTMRInitialize(&digInputTimerData, &tmrSettings);
    halINTSetInterruptVectorPriority(DigInputService_TimerInterruptVector, DigInputService_TimerInterruptPriority, DigInputService_TimerInterruptSubPriority);
    halINTEnableInterruptVector(DigInputService_TimerInterruptVector);

	// Inicialitza el temporitzador per les sortides digitals
	//
	tmrSettings.timer = DigOutputService_Timer;
#if defined(EOS_PIC32)
    tmrSettings.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_64;
    tmrSettings.period = ((halSYSGetPeripheralClockFrequency() * DigOutputService_TimerPeriod) / 64000) - 1;
#elif defined(EOS_STM32F4) || defined(EOS_STM32F7)
    tmrSettings.options = HAL_TMR_MODE_16 | HAL_TMR_CLKDIV_1;
    tmrSettings.prescaler = (halSYSGetTimerClock1Frequency() / 1000000L) - 1; // 1MHz
    tmrSettings.period = (1000 * DigOutputService_TimerPeriod) - 1;
#else
    #error CPU no soportada
#endif
	halTMRInitialize(&digOutputTimerData, &tmrSettings);
    halINTSetInterruptVectorPriority(DigOutputService_TimerInterruptVector, DigOutputService_TimerInterruptPriority, DigOutputService_TimerInterruptSubPriority);
    halINTEnableInterruptVector(DigOutputService_TimerInterruptVector);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els serveis associats a l'aplicacio.
///
void MyApplication::initializeServices() {

    // Inicialitza el servei d'entrades digitals
	//
    DigInputService::Settings digInputServiceSettings;
    DigInput::Settings digInputSettings;

    digInputServiceSettings.hTimer = &digInputTimerData;
    digInputService = new DigInputService(this, digInputServiceSettings);
    digInputService->setPriority(Task::Priority::high);

    digInputSettings.eventParam = nullptr;

    digInputSettings.port = SWITCHES_SW1_PORT;
    digInputSettings.pin = SWITCHES_SW1_PIN;
    digInputSettings.eventCallback = &sw1EventCallback;
    sw1 = new DigInput(digInputService, digInputSettings);

#ifdef EXIST_SWITCHES_SW2
    digInputSettings.port = SWITCHES_SW2_PORT;
    digInputSettings.pin = SWITCHES_SW2_PIN;
    digInputSettings.eventCallback = &sw2EventCallback;
    sw2 = new DigInput(digInputService, digInputSettings);
#endif

#ifdef EXIST_SWITCHES_SW3
    digInputSettings.port = SWITCHES_SW3_PORT;
    digInputSettings.pin = SWITCHES_SW3_PIN;
    digInputSettings.eventCallback = &sw3EventCallback;
    sw3 = new DigInput(digInputService, digInputSettings);
#endif

    // Inicialitza el servei de sortides digitals
    //
    DigOutputService::Settings digOutputServiceSettings;
    DigOutput::Settings digOutputSettings;

    digOutputServiceSettings.hTimer = &digOutputTimerData;
    digOutputService = new DigOutputService(this, digOutputServiceSettings);

    digOutputSettings.port = LEDS_LED1_PORT;
    digOutputSettings.pin = LEDS_LED1_PIN;
    led1 = new DigOutput(digOutputService, digOutputSettings);
    led1->write(LEDS_STATE_OFF);

#ifdef EXIST_LEDS_LED2
    digOutputSettings.port = LEDS_LED2_PORT;
    digOutputSettings.pin = LEDS_LED2_PIN;
    led2 = new DigOutput(digOutputService, digOutputSettings);
    led2->write(LEDS_STATE_OFF);
#endif

#ifdef EXIST_LEDS_LED3
    digOutputSettings.port = LEDS_LED3_PORT;
    digOutputSettings.pin = LEDS_LED3_PIN;
    led3 = new DigOutput(digOutputService, digOutputSettings);
    led3->write(LEDS_STATE_OFF);
#endif

	// Inicialitza el servei UartService
	//
	UARTService::Settings uartServiceSettings;
	uartServiceSettings.hUART = &uartData;
	uartService = new UARTService(this, uartServiceSettings);

	// Inicialitza el servei AppLoop
	//
	loopService = new MyAppLoopService(this);
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW1
void MyApplication::sw1EventHandler(
    const DigInput::EventArgs &args) {

    if (sw1->read() == SWITCHES_STATE_ON) {
        led1->pulse(1000);
        uartService->send((uint8_t*) "hola\r\n", 6, unsigned(-1));
#ifdef ESIST_LEDS_LED2
        led2->delayedPulse(500, 500);
#endif
#ifdef EXIST_LEDS_LED3
        led3->delayedPulse(500, 500);
#endif
    }
}
#endif


/// --------------------------------------------------------------------
/// \brief    Procesa els events de switch 2.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW2
void MyApplication::sw2EventHandler(
    const DigInput::EventArgs &args) {

    if (sw2->read() == SWITCHES_STATE_ON) {
#ifdef EXIST_LEDS_LED3
        led3->pulse(500);
#endif
#ifdef EXIST_LEDS_LED2
        led2->delayedPulse(250, 500);
#endif
        led1->delayedPulse(500, 500);
    }
}
#endif


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 3.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW3
void MyApplication::sw3EventHandler(
    const DigInput::EventArgs &args) {

    if (sw3->read() == SWITCHES_STATE_ON) {
        led1->pulse(1000);
#ifdef EXIST_LEDS_LED2
        led2->pulse(2000);
#endif
#ifdef EXIST_LEDS_LED3
        led3->pulse(3000);
#endif
    }
}
#endif


