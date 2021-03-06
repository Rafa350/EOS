#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "HAL/PIC32/halCN.h"
#include "Services/eosAppLoopService.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "Services/eosFsmService.h"
#include "System/eosApplication.h"

#include "appApplication.h"
#include "appStateMachine.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
MyApplication::MyApplication():
    digInput1EventCallback(this, &MyApplication::digInput1EventHandler),
    digInput2EventCallback(this, &MyApplication::digInput2EventHandler),
    digInput3EventCallback(this, &MyApplication::digInput3EventHandler),
    fsmEventCallback(this, &MyApplication::fsmEventHandler) {

    // Crea els serveis necesaris
    //
    digInputService = new DigInputService(this);
    DigOutputService::Settings digOutputServiceSettings {
        .hTimer = HAL_TMR_TIMER_2
    };
    digOutputService = new DigOutputService(this, digOutputServiceSettings);
    fsmService = new FsmService(this);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    // Inicialitza el servei d'entrades digitals
	//
#ifdef EXIST_SWITCHES_SW1
    digInput1 = new DigInput(
        digInputService,
        SW_SW1_PORT,
        SW_SW1_PIN);
    digInput1->setEventCallback(&digInput1EventCallback);
#endif

#ifdef EXIST_SWITCHES_SW2
    digInput2 = new DigInput(
        digInputService,
        SW_SW2_PORT,
        SW_SW2_PIN);
    digInput2->setEventCallback(&digInput2EventCallback);
#endif

#ifdef EXIST_SWITCHES_SW3
    digInput3 = new DigInput(
        digInputService,
        SW_SW3_PORT,
        SW_SW3_PIN);
    digInput3->setEventCallback(&digInput3EventCallback);
#endif

    // Inicialitza el servei de sortides digitals
    //
#ifdef EXIST_LEDS_LED1
    digOutput1 = new DigOutput(
        digOutputService,
        LEDS_LED1_PORT,
        LEDS_LED1_PIN,
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR);
#endif

#ifdef EXIST_LEDS_LED2
    digOutput2 = new DigOutput(
        digOutputService,
        LEDS_LED2_PORT,
        LEDS_LED2_PIN,
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR);
#endif

#ifdef EXIST_LEDS_LED3
    digOutput3 = new DigOutput(
        digOutputService,
        LEDS_LED3_PORT,
        LEDS_LED3_PIN,
        HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR);
#endif

    // Inicialitza el servei de maquina d'estat
    //
    sm = new MyStateMachine();
    fsmService->addMachine(sm);
    fsmService->setEventCallback(&fsmEventCallback);
}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del servei 'FSM'
/// \param    args: Parametres del event.
///
void MyApplication::fsmEventHandler(
    const FsmService::EventArgs& args) {

}


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 1.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW1
void MyApplication::digInput1EventHandler(
    const DigInput::EventArgs &args) {

    if (!args.input->get())
        sm->acceptMessage(MyStateMachine::Message::pressedSW1, (unsigned) -1);
}
#endif


/// --------------------------------------------------------------------
/// \brief    Procesa els events de switch 2.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW2
void MyApplication::digInput2EventHandler(
    const DigInput::EventArgs &args) {

    if (!args.input->get())
        sm->acceptMessage(MyStateMachine::Message::pressedSW2, (unsigned) -1);
}
#endif


/// --------------------------------------------------------------------
/// \brief    Procesa els events del switch 3.
/// \param    args: Parametres del event.
///
#ifdef EXIST_SWITCHES_SW3
void MyApplication::digInput3EventHandler(
    const DigInput::EventArgs &args) {

    if (!args.input->get())
        sm->acceptMessage(MyStateMachine::Message::pressedSW3, (unsigned) -1);
}
#endif
