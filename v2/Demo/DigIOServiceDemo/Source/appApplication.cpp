#include "eos.h"
#include "HAL/halGPIO.h"
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
    digInput1EventCallback(this, &MyApplication::digInput1EventHandler),
    digInput2EventCallback(this, &MyApplication::digInput2EventHandler),
    digInput3EventCallback(this, &MyApplication::digInput3EventHandler) {
    
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    // Inicialitza el servei d'entrades digitals
	//
    DigInputService::InitParams digInputServiceInit;
    digInputServiceInit.timer = HAL_TMR_TIMER_3;
    digInputServiceInit.period = 10;
    digInputService = new DigInputService(this, digInputServiceInit);
    
    DigInput::InitParams digInputInit;
    digInputInit.eventParam = nullptr;
    
    // Inicialitza la entrada corresponent al switch SW1
    //
#ifdef EXIST_SWITCHES_SW1
    halGPIOInitializePin(SW_SW1_PORT, SW_SW1_PIN, 
        HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);

    digInputInit.port = SW_SW1_PORT;
    digInputInit.pin = SW_SW1_PIN;
    digInputInit.eventCallback = &digInput1EventCallback;
    digInput1 = new DigInput(digInputService, digInputInit);
#endif

    // Inicialitza la entrada corresponent al switch SW2
    //
#ifdef EXIST_SWITCHES_SW2
    halGPIOInitializePin(SW_SW2_PORT, SW_SW2_PIN, 
        HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);

    digInputInit.port = SW_SW2_PORT;
    digInputInit.pin = SW_SW2_PIN;
    digInputInit.eventCallback = &digInput2EventCallback;
    digInput2 = new DigInput(digInputService, digInputInit);
#endif

    // Inicialitza la entrada corresponent al switch SW3
    //
#ifdef EXIST_SWITCHES_SW3
    halGPIOInitializePin(SW_SW3_PORT, SW_SW3_PIN, 
        HAL_GPIO_MODE_INPUT, HAL_GPIO_AF_NONE);

    digInputInit.port = SW_SW3_PORT;
    digInputInit.pin = SW_SW3_PIN;
    digInputInit.eventCallback = &digInput3EventCallback;
    digInput3 = new DigInput(digInputService, digInputInit);
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
    digOutput1 = new DigOutput(digOutputService, digOutputInit);
#endif

    // Inicialitza la sortida corresponent al led LED2
    //
#ifdef EXIST_LEDS_LED2
    halGPIOInitializePin(LED_LED2_PORT, LED_LED2_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE);

    digOutputInit.port = LED_LED2_PORT;
    digOutputInit.pin = LED_LED2_PIN;
    digOutput2 = new DigOutput(digOutputService, digOutputInit);
#endif

    // Inicialitza la sortida corresponent al led LED3
    //
#ifdef EXIST_LEDS_LED3
    halGPIOInitializePin(LED_LED3_PORT, LED_LED3_PIN, 
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE);
    
    digOutputInit.port = LED_LED3_PORT;
    digOutputInit.pin = LED_LED3_PIN;
    digOutput3 = new DigOutput(digOutputService, digOutputInit);
#endif
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW1
void MyApplication::digInput1EventHandler(
    const DigInput::EventArgs &args) {

#ifdef EXIST_LEDS_LED1
    if (!args.input->get()) {
        getLed1()->pulse(500);
        getLed2()->delayedPulse(250, 500);
        getLed3()->delayedPulse(500, 500);
    }
#endif
}
#endif


/// --------------------------------------------------------------------
/// \brief    Procesa els events de switch 2.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW2
void MyApplication::digInput2EventHandler(
    const DigInput::EventArgs &args) {

#ifdef EXIST_LEDS_LED2
    if (!args.input->get()) {
        getLed3()->pulse(500);
        getLed2()->delayedPulse(250, 500);
        getLed1()->delayedPulse(500, 500);
    }
#endif
}
#endif


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 3.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW3
void MyApplication::digInput3EventHandler(
    const DigInput::EventArgs &args) {

#ifdef EXIST_LEDS_LED3
    if (!args.input->get()) {
        getLed1()->toggle();
        getLed2()->toggle();
        getLed3()->toggle();
    }
#endif
}
#endif
