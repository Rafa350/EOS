#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "HAL/halEXTI.h"
#include "Services/eosAppLoop.h"
#include "Services/eosDigOutput.h"
#include "Services/eosDigInput.h"
#include "System/eosApplication.h"


using namespace eos;


class MyApplication: public Application {
    private:
        DigOutputService *digOutputSrv;
#ifdef EXIST_LEDS_LED1
        DigOutput *digOutput1;
#endif
#ifdef EXIST_LEDS_LED2
        DigOutput *digOutput2;
#endif
#ifdef EXIST_LEDS_LED3
        DigOutput *digOutput3;
#endif
        DigInputService *digInputSvc;
#ifdef EXIST_SWITCHES_SW1
        DigInput *digInput1;
#endif
#ifdef EXIST_SWITCHES_SW2
        DigInput *digInput2;
#endif
#ifdef EXIST_SWITCHES_SW3
        DigInput *digInput3;
#endif

    public:
#ifdef EXIST_SWITCHES_SW1
        void digInput1_OnChange(DigInput *input);
#endif
#ifdef EXIST_SWITCHES_SW2
        void digInput2_OnChange(DigInput *input);
#endif
#ifdef EXIST_SWITCHES_SW3
        void digInput3_OnChange(DigInput *input);
#endif

#ifdef EXIST_LEDS_LED1
        DigOutput *getLed1() const { return digOutput1; }
#endif
#ifdef EXIST_LEDS_LED2
        DigOutput *getLed2() const { return digOutput2; }
#endif
#ifdef EXIST_LEDS_LED3
        DigOutput *getLed3() const { return digOutput3; }
#endif

    protected:
        void onInitialize();
};


class LedLoopService: public AppLoopService {
    protected:
		void onLoop();

    public:
		LedLoopService(Application *application);
};


static void initEXTI() {
    
    EXTIInitializeLineInfo extiConfiguration;
    extiConfiguration.line = HAL_EXTI_LINE_19;
    extiConfiguration.options = HAL_EXTI_TRIGGER_FALLING | HAL_EXTI_ENABLE_YES;
    halEXTIInitializeLines(&extiConfiguration, 1);
    uint32_t dummy = halGPIOReadPort(HAL_GPIO_PORT_D);
}


/// ---------------------------------------------------------------------------
/// \brief Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    // Prepara el servei d'entrades digitals
	//
    digInputSvc = new DigInputService(this);

	DigInputConfiguration inputConfiguration;

#ifdef EXIST_SWITCHES_SW1
    inputConfiguration.port = SW_SW1_PORT;
    inputConfiguration.pin = SW_SW1_PIN;
    digInput1 = new DigInput(digInputSvc, inputConfiguration);
    digInput1->setChangeEvent<MyApplication>(this, &MyApplication::digInput1_OnChange);
#endif

#ifdef EXIST_SWITCHES_SW2
    inputConfiguration.port = SW_SW2_PORT;
    inputConfiguration.pin = SW_SW2_PIN;
    digInput2 = new DigInput(digInputSvc, inputConfiguration);
    digInput2->setChangeEvent<MyApplication>(this, &MyApplication::digInput2_OnChange);
#endif

#ifdef EXIST_SWITCHES_SW3
    inputConfiguration.port = SW_SW3_PORT;
    inputConfiguration.pin = SW_SW3_PIN;
    digInput3 = new DigInput(digInputSvc, inputConfiguration);
    digInput3->setChangeEvent<MyApplication>(this, &MyApplication::digInput3_OnChange);
#endif

    // Prepara el servei de sortides digitals
    //
    DigOutputServiceConfiguration outputSrvConfiguration;
    outputSrvConfiguration.timer = HAL_TMR_TIMER_2;
    digOutputSrv = new DigOutputService(this, outputSrvConfiguration);

    DigOutputConfiguration outputConfiguration;
    outputConfiguration.openDrain = false;
    outputConfiguration.initState = false;

#ifdef EXIST_LEDS_LED1
    outputConfiguration.port = LED_LED1_PORT;
    outputConfiguration.pin = LED_LED1_PIN;
    digOutput1 = new DigOutput(digOutputSrv, outputConfiguration);
#endif

#ifdef EXIST_LEDS_LED2
    outputConfiguration.port = LED_LED2_PORT;
    outputConfiguration.pin = LED_LED2_PIN;
    digOutput2 = new DigOutput(digOutputSrv, outputConfiguration);
#endif

#ifdef EXIST_LEDS_LED3
    outputConfiguration.port = LED_LED3_PORT;
    outputConfiguration.pin = LED_LED3_PIN;
    digOutput3 = new DigOutput(digOutputSrv, outputConfiguration);
#endif

    // Prepara el servei de l'aplicacio principal
    //
    new LedLoopService(this);
    
    // Prepara la linia d'interrupcio pel boto SW3 (RD13/CN19)
    //
    //initEXTI();
}


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
#ifdef EXIST_SWITCHES_SW1
void MyApplication::digInput1_OnChange(DigInput *input) {

#ifdef EXIST_LEDS_LED3
    if (!input->get()) 
        getLed3()->pulse(500);
#endif    
}
#endif


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
#ifdef EXIST_SWITCHES_SW2
void MyApplication::digInput2_OnChange(DigInput *input) {

#ifdef EXIST_LEDS_LED3
    if (!input->get()) 
        getLed3()->pulse(1000);
#endif    
}
#endif


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
#ifdef EXIST_SWITCHES_SW3
void MyApplication::digInput3_OnChange(DigInput *input) {

#ifdef EXIST_LEDS_LED3
    if (!input->get()) 
        getLed3()->pulse(1500);
#endif    
}
#endif


/// ---------------------------------------------------------------------
/// \brief Constructor.
/// \param application: Aplicacio a la que pertany el servei.
///
LedLoopService::LedLoopService(
    Application* application):

    AppLoopService(application) {
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio de la tasca del servei.
///
void LedLoopService::onLoop() {

    MyApplication *app = (MyApplication*) getApplication();
    
#ifdef EXIST_LEDS_LED1    
    app->getLed1()->pulse(500);
#endif    
    
#ifdef EXIST_LEDS_LED2    
    app->getLed2()->delayedPulse(125, 250);
#endif    
       
    Task::delay(1000);
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void appMain() {

	Application *app = new MyApplication();
	app->run();
	delete app;
}
