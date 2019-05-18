#include "System/eosApplication.h"
#include "Services/eosAppLoop.h"
#include "Services/eosDigOutput.h"
#include "Services/eosDigInput.h"
#include "hal/halGPIO.h"
#include "hal/halTMR.h"


using namespace eos;


class MyApplication: public Application {
    private:
        DigOutputService *digOutputSrv;
#ifdef USE_LEDS_LED1
        DigOutput *digOutput1;
#endif
#ifdef USE_LEDS_LED2
        DigOutput *digOutput2;
#endif
#ifdef USE_LEDS_LED3
        DigOutput *digOutput3;
#endif
        DigInputService *digInputSvc;
#ifdef USE_SWITCHES_SW1
        DigInput *digInput1;
#endif
#ifdef USE_SWITCHES_SW2
        DigInput *digInput2;
#endif
#ifdef USE_SWITCHES_SW3
        DigInput *digInput3;
#endif

    public:
#ifdef USE_SWITCHES_SW1
        void digInput1_OnChange(DigInput *input);
#endif
#ifdef USE_SWITCHES_SW2
        void digInput2_OnChange(DigInput *input);
#endif
#ifdef USE_SWITCHES_SW3
        void digInput3_OnChange(DigInput *input);
#endif

#ifdef USE_LEDS_LED1
        DigOutput *getLed1() const { return digOutput1; }
#endif
#ifdef USE_LEDS_LED2
        DigOutput *getLed2() const { return digOutput2; }
#endif
#ifdef USE_LEDS_LED3
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



/// ---------------------------------------------------------------------------
/// \brief Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    // Prepara el servei d'entrades digitals
	//
    digInputSvc = new DigInputService(this, nullptr);

	DigInputInitializeInfo inputInfo;

#ifdef USE_SWITCHES_SW1
    inputInfo.port = SW_SW1_PORT;
    inputInfo.pin = SW_SW1_PIN;
    digInput1 = new DigInput(digInputSvc, &inputInfo);
    digInput1->setChangeEvent<MyApplication>(this, &MyApplication::digInput1_OnChange);
#endif

#ifdef USE_SWITCHES_SW2
    inputInfo.port = SW_SW2_PORT;
    inputInfo.pin = SW_SW2_PIN;
    digInput2 = new DigInput(digInputSvc, &inputInfo);
    digInput2->setChangeEvent<MyApplication>(this, &MyApplication::digInput2_OnChange);
#endif

#ifdef USE_SWITCHES_SW3
    inputInfo.port = SW_SW3_PORT;
    inputInfo.pin = SW_SW3_PIN;
    digInput3 = new DigInput(digInputSvc, &inputInfo);
    digInput3->setChangeEvent<MyApplication>(this, &MyApplication::digInput3_OnChange);
#endif

    // Prepara el servei de sortides digitals
    //
    DigOutputServiceInitializeInfo outputSrvInfo;
    outputSrvInfo.timer = HAL_TMR_TIMER_2;
    digOutputSrv = new DigOutputService(this, &outputSrvInfo);

    DigOutputInitializeInfo outputInfo;
    outputInfo.openDrain = false;
    outputInfo.initState = false;

#ifdef USE_LEDS_LED1
    outputInfo.port = LED_LED1_PORT;
    outputInfo.pin = LED_LED1_PIN;
    digOutput1 = new DigOutput(digOutputSrv, &outputInfo);
#endif

#ifdef USE_LEDS_LED2
    outputInfo.port = LED_LED2_PORT;
    outputInfo.pin = LED_LED2_PIN;
    digOutput2 = new DigOutput(digOutputSrv, &outputInfo);
#endif

#ifdef USE_LEDS_LED3
    outputInfo.port = LED_LED3_PORT;
    outputInfo.pin = LED_LED3_PIN;
    digOutput3 = new DigOutput(digOutputSrv, &outputInfo);
#endif

    // Prepara el servei de l'aplicacio principal
    //
    new LedLoopService(this);
}


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
#ifdef USE_SWITCHES_SW1
void MyApplication::digInput1_OnChange(DigInput *input) {

#ifdef USE_LEDS_LED3
    if (!input->get()) 
        getLed3()->pulse(500);
#endif    
}
#endif


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
#ifdef USE_SWITCHES_SW2
void MyApplication::digInput2_OnChange(DigInput *input) {

#ifdef USE_LEDS_LED3
    if (!input->get()) 
        getLed3()->pulse(1000);
#endif    
}
#endif


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
#ifdef USE_SWITCHES_SW3
void MyApplication::digInput3_OnChange(DigInput *input) {

#ifdef USE_LEDS_LED3
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
    
#ifdef USE_LEDS_LED1    
    app->getLed1()->pulse(500);
#endif    
    
#ifdef USE_LEDS_LED2    
    app->getLed2()->delayedPulse(125, 250);
#endif    
       
    Task::delay(1000);
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void AppMain() {

	Application *app = new MyApplication();
	app->run();
	delete app;
}
