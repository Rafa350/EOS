#include "eos.h"
#include "HAL/halGPIO.h"
#include "HAL/halTMR.h"
#include "HAL/PIC32/halCN.h"
#include "Services/eosAppLoopService.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "System/eosApplication.h"


using namespace eos;


class MyApplication: public Application {
    private:
		typedef CallbackP1<MyApplication, const DigInput::EventArgs&> DigInputEventCallback;
        
    private:
        DigOutputService *digOutputService;
#ifdef EXIST_LEDS_LED1
        DigOutput *digOutput1;
#endif
#ifdef EXIST_LEDS_LED2
        DigOutput *digOutput2;
#endif
#ifdef EXIST_LEDS_LED3
        DigOutput *digOutput3;
#endif
        DigInputService *digInputService;
#ifdef EXIST_SWITCHES_SW1
        DigInput *digInput1;
        DigInputEventCallback digInput1EventCallback;
#endif
#ifdef EXIST_SWITCHES_SW2
        DigInput *digInput2;
        DigInputEventCallback digInput2EventCallback;
#endif
#ifdef EXIST_SWITCHES_SW3
        DigInput *digInput3;
        DigInputEventCallback digInput3EventCallback;
#endif

    public:
        MyApplication();
#ifdef EXIST_SWITCHES_SW1
        void digInput1_OnChange(const DigInput::EventArgs &args);
#endif
#ifdef EXIST_SWITCHES_SW2
        void digInput2_OnChange(const DigInput::EventArgs &args);
#endif
#ifdef EXIST_SWITCHES_SW3
        void digInput3_OnChange(const DigInput::EventArgs &args);
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


static void initCN() {
    
    CNInitializeLineInfo extiConfiguration;
    extiConfiguration.line = HAL_CN_LINE_19;
    extiConfiguration.options = HAL_CN_TRIGGER_FALLING | HAL_CN_ENABLE_YES;
    halCNInitializeLines(&extiConfiguration, 1);
    uint32_t dummy = halGPIOReadPort(HAL_GPIO_PORT_D);
}


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
MyApplication::MyApplication():
    digInput1EventCallback(this, &MyApplication::digInput1_OnChange), 
    digInput2EventCallback(this, &MyApplication::digInput2_OnChange), 
    digInput3EventCallback(this, &MyApplication::digInput3_OnChange) {
    
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    // Prepara el servei d'entrades digitals
	//
    digInputService = new DigInputService(this);

	DigInput::Configuration inputConfiguration;

#ifdef EXIST_SWITCHES_SW1
    inputConfiguration.port = SW_SW1_PORT;
    inputConfiguration.pin = SW_SW1_PIN;
    digInput1 = new DigInput(digInputService, &inputConfiguration);
    digInput1->setChangeEventCallback(&digInput1EventCallback);
#endif

#ifdef EXIST_SWITCHES_SW2
    inputConfiguration.port = SW_SW2_PORT;
    inputConfiguration.pin = SW_SW2_PIN;
    digInput2 = new DigInput(digInputService, &inputConfiguration);
    digInput2->setChangeEventCallback(&digInput2EventCallback);
#endif

#ifdef EXIST_SWITCHES_SW3
    inputConfiguration.port = SW_SW3_PORT;
    inputConfiguration.pin = SW_SW3_PIN;
    digInput3 = new DigInput(digInputService, &inputConfiguration);
    digInput3->setChangeEventCallback(&digInput3EventCallback);
#endif

    // Prepara el servei de sortides digitals
    //
    DigOutputService::Configuration digOutputServiceConfiguration;
    digOutputServiceConfiguration.serviceConfiguration = nullptr;
    digOutputServiceConfiguration.timer = HAL_TMR_TIMER_2;
    digOutputService = new DigOutputService(this, &digOutputServiceConfiguration);

    DigOutput::Configuration outputConfiguration;
    outputConfiguration.options = HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR;

#ifdef EXIST_LEDS_LED1
    outputConfiguration.port = LED_LED1_PORT;
    outputConfiguration.pin = LED_LED1_PIN;
    digOutput1 = new DigOutput(digOutputService, &outputConfiguration);
#endif

#ifdef EXIST_LEDS_LED2
    outputConfiguration.port = LED_LED2_PORT;
    outputConfiguration.pin = LED_LED2_PIN;
    digOutput2 = new DigOutput(digOutputService, &outputConfiguration);
#endif

#ifdef EXIST_LEDS_LED3
    outputConfiguration.port = LED_LED3_PORT;
    outputConfiguration.pin = LED_LED3_PIN;
    digOutput3 = new DigOutput(digOutputService, &outputConfiguration);
#endif

    // Prepara el servei de l'aplicacio principal
    //
    new LedLoopService(this);
    
    // Prepara la linia d'interrupcio pel boto SW3 (RD13/CN19)
    //
    //initCN();
}


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
#ifdef EXIST_SWITCHES_SW1
void MyApplication::digInput1_OnChange(const DigInput::EventArgs &args) {

#ifdef EXIST_LEDS_LED3
    if (!args.input->get()) 
        getLed3()->pulse(500);
#endif    
}
#endif


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
#ifdef EXIST_SWITCHES_SW2
void MyApplication::digInput2_OnChange(const DigInput::EventArgs &args) {

#ifdef EXIST_LEDS_LED3
    if (!args.input->get()) 
        getLed3()->pulse(1000);
#endif    
}
#endif


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
#ifdef EXIST_SWITCHES_SW3
void MyApplication::digInput3_OnChange(const DigInput::EventArgs &args) {

#ifdef EXIST_LEDS_LED3
    if (!args.input->get()) 
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
