#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "Services/eosAppLoopService.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "System/eosApplication.h"

#include "appApplication.h"
#include "appLedLoopService.h"



using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication():
    digInput1EventCallback(this, &MyApplication::digInput1EventHandler),
    digInput2EventCallback(this, &MyApplication::digInput2EventHandler),
    digInput3EventCallback(this, &MyApplication::digInput3EventHandler),
    timerEventCallback(this, &MyApplication::timerEventHandler) {
    
    // Crea els serveis necesaris
    //
    digInputService = new DigInputService(this);
    digOutputService = new DigOutputService(this, HAL_TMR_TIMER_2);
    ledLoopService = new LedLoopService(this);
    timerService = new TimerService(this);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    // Inicialitza el servei d'entrades digitals
	//
#ifdef EXIST_SWITCHES_SW1
    digInput1 = new DigInput(digInputService, SW_SW1_PORT, SW_SW1_PIN);
    digInput1->setEventCallback(&digInput1EventCallback);
#endif

#ifdef EXIST_SWITCHES_SW2
    digInput2 = new DigInput(digInputService, SW_SW2_PORT, SW_SW2_PIN);
    digInput2->setEventCallback(&digInput2EventCallback);
#endif

#ifdef EXIST_SWITCHES_SW3
    digInput3 = new DigInput(digInputService, SW_SW3_PORT, SW_SW3_PIN);
    digInput3->setEventCallback(&digInput3EventCallback);
#endif

    // Inicialitza el servei de sortides digitals
    //
#ifdef EXIST_LEDS_LED1
    digOutput1 = new DigOutput(digOutputService, LED_LED1_PORT, LED_LED1_PIN,
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR);
#endif

#ifdef EXIST_LEDS_LED2
    digOutput2 = new DigOutput(digOutputService, LED_LED2_PORT, LED_LED2_PIN,
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR);
#endif

#ifdef EXIST_LEDS_LED3
    digOutput3 = new DigOutput(digOutputService, LED_LED3_PORT, LED_LED3_PIN,
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR);
#endif

    // Inicialitza el servei de temporitzadors.
    //
    timer1 = new TimerCounter(timerService);
    timer1->setEventCallback(&timerEventCallback);

    timer2 = new TimerCounter(timerService);
    timer2->setEventCallback(&timerEventCallback);
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del temporitzador 1 i 2.
/// \param    args: Parametres del event.
///
void MyApplication::timerEventHandler(
    const TimerCounter::EventArgs& args) {

#ifdef EXIST_LEDS_LED3
    getLed3()->pulse(250);
#endif
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW1
void MyApplication::digInput1EventHandler(
    const DigInput::EventArgs &args) {

#ifdef EXIST_LEDS_LED3
    if (!args.input->get())
        //getLed3()->pulse(500);
        getLed3()->toggle();
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

#ifdef EXIST_LEDS_LED3
    if (!args.input->get())
        getLed3()->pulse(1000);
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
    //    getLed3()->pulse(1500);
        timer1->start(1000);
        timer2->start(1500);
    }
#endif
}
#endif
