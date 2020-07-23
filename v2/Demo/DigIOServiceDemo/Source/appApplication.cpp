#include "eos.h"
#include "HAL/halGPIO.h"
#ifdef EOS_PIC32
#include "HAL/PIC32/halCN.h"
#endif
#include "HAL/halTMR.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "System/eosApplication.h"

#include "appApplication.h"


using namespace eos;
using namespace app;


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

    // Inicialitza el servei d'entrades digitals
	//
    DigInputService::InitParams digInputServiceInit;
    digInputServiceInit.timer = HAL_TMR_TIMER_3;
    digInputServiceInit.period = 5;
    digInputService = new DigInputService(this, digInputServiceInit);
    digInputService->setPriority(Task::Priority::high);
    
    DigInput::InitParams digInputInit;
    digInputInit.eventParam = nullptr;
    
    // Inicialitza la entrada corresponent al switch SW1
    //
#ifdef EXIST_SWITCHES_SW1
    halGPIOInitializePin(SW_SW1_PORT, SW_SW1_PIN, 
        HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);
#ifdef EOS_PIC32
    halCNInitializeLine(SW_SW1_CN, HAL_CN_PULL_UP);
#endif

    digInputInit.port = SW_SW1_PORT;
    digInputInit.pin = SW_SW1_PIN;
    digInputInit.eventCallback = &sw1EventCallback;
    sw1 = new DigInput(digInputService, digInputInit);
#endif

    // Inicialitza la entrada corresponent al switch SW2
    //
#ifdef EXIST_SWITCHES_SW2
    halGPIOInitializePin(SW_SW2_PORT, SW_SW2_PIN, 
        HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);
    halCNInitializeLine(SW_SW2_CN, HAL_CN_PULL_UP);

    digInputInit.port = SW_SW2_PORT;
    digInputInit.pin = SW_SW2_PIN;
    digInputInit.eventCallback = &sw2EventCallback;
    sw2 = new DigInput(digInputService, digInputInit);
#endif

    // Inicialitza la entrada corresponent al switch SW3
    //
#ifdef EXIST_SWITCHES_SW3
    halGPIOInitializePin(SW_SW3_PORT, SW_SW3_PIN, 
        HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);
    halCNInitializeLine(SW_SW3_CN, HAL_CN_PULL_UP);

    digInputInit.port = SW_SW3_PORT;
    digInputInit.pin = SW_SW3_PIN;
    digInputInit.eventCallback = &sw3EventCallback;
    sw3 = new DigInput(digInputService, digInputInit);
#endif

    // Inicialitza el servei de sortides digitals
    //
    DigOutputService::InitParams digOutputServiceInit;
    digOutputServiceInit.timer = HAL_TMR_TIMER_2;
    digOutputServiceInit.period = 1;
    digOutputService = new DigOutputService(this, digOutputServiceInit);
    
    DigOutput::InitParams digOutputInit;

    // Inicialitza la sortida corresponent al led LED1
    //
#ifdef EXIST_LEDS_LED1
    halGPIOInitializePin(LED_LED1_PORT, LED_LED1_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE);

    digOutputInit.port = LED_LED1_PORT;
    digOutputInit.pin = LED_LED1_PIN;
    led1 = new DigOutput(digOutputService, digOutputInit);
#endif

    // Inicialitza la sortida corresponent al led LED2
    //
#ifdef EXIST_LEDS_LED2
    halGPIOInitializePin(LED_LED2_PORT, LED_LED2_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE);

    digOutputInit.port = LED_LED2_PORT;
    digOutputInit.pin = LED_LED2_PIN;
    led2 = new DigOutput(digOutputService, digOutputInit);
#endif

    // Inicialitza la sortida corresponent al led LED3
    //
#ifdef EXIST_LEDS_LED3
    halGPIOInitializePin(LED_LED3_PORT, LED_LED3_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE);
    
    digOutputInit.port = LED_LED3_PORT;
    digOutputInit.pin = LED_LED3_PIN;
    led3 = new DigOutput(digOutputService, digOutputInit);
#endif

}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW1
void MyApplication::sw1EventHandler(
    const DigInput::EventArgs &args) {

    if (!sw1->read()) {
        led1->pulse(500);
        led2->delayedPulse(250, 500);
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

    if (!sw2->read()) {
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

    bool value = !sw3->read();
    led1->write(value);
#ifdef EXIST_LEDS_LED2
    led2->write(value);
#endif
#ifdef EXIST_LEDS_LED3
    led3->write(value);
#endif
}
#endif
