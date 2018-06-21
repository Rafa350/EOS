#include "System/eosApplication.h"
#include "Services/eosAppLoop.h"
#include "Services/eosDigOutput.h"
#include "Services/eosDigInput.h"
#include "hal/halGPIO.h"


using namespace eos;


class LedLoopService: public AppLoopService {
    private:
        DigOutput *output1;
        DigOutput *output2;

	public:
		LedLoopService(Application *application, DigOutput *output1, DigOutput *output2);

    protected:
		void onLoop();
};


class MyApplication: public Application {
    private:
        DigInputService *digInputSvc;
        DigInput *digInput1;
        DigInput *digInput2;
        DigInput *digInput3;
        DigOutputService *digOutputSrv;
        DigOutput *digOutput1;
        DigOutput *digOutput2;
        DigOutput *digOutput3;

    public:
        void digInput1_OnChange(DigInput *input);
        void digInput2_OnChange(DigInput *input);
        void digInput3_OnChange(DigInput *input);

    protected:
        void onInitialize();
};


/// ---------------------------------------------------------------------------
/// \brief Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {

    // Prepara el servei d'entrades digitals
	//
    digInputSvc = new DigInputService(this, nullptr);

	DigInputInitializeInfo inputInfo;

#ifdef SW_SW1_PIN
    inputInfo.port = SW_SW1_PORT;
    inputInfo.pin = SW_SW1_PIN;
    digInput1 = new DigInput(digInputSvc, &inputInfo);
    digInput1->setChangeEvent<MyApplication>(this, &MyApplication::digInput1_OnChange);
#endif

#ifdef SW_SW2_PIN
    inputInfo.port = SW_SW2_PORT;
    inputInfo.pin = SW_SW2_PIN;
    digInput2 = new DigInput(digInputSvc, &inputInfo);
    digInput2->setChangeEvent<MyApplication>(this, &MyApplication::digInput2_OnChange);
#endif

#ifdef SW_SW3_PIN
    inputInfo.port = SW_SW3_PORT;
    inputInfo.pin = SW_SW3_PIN;
    digInput3 = new DigInput(digInputSvc, &inputInfo);
    digInput3->setChangeEvent<MyApplication>(this, &MyApplication::digInput3_OnChange);
#endif

    // Prepara el servei de sortides digitals
    //
    digOutputSrv = new DigOutputService(this, nullptr);

    DigOutputInitializeInfo outputInfo;
    outputInfo.openDrain = false;
    outputInfo.initState = false;

#ifdef LED_LED1_PIN
    outputInfo.port = LED_LED1_PORT;
    outputInfo.pin = LED_LED1_PIN;
    digOutput1 = new DigOutput(digOutputSrv, &outputInfo);
#endif

#ifdef LED_LED2_PIN
    outputInfo.port = LED_LED2_PORT;
    outputInfo.pin = LED_LED2_PIN;
    digOutput2 = new DigOutput(digOutputSrv, &outputInfo);
#endif

#ifdef LED_LED3_PIN
    outputInfo.port = LED_LED3_PORT;
    outputInfo.pin = LED_LED3_PIN;
    digOutput3 = new DigOutput(digOutputSrv, &outputInfo);
#endif

    // Prepara el servei de l'aplicacio
    //
    new LedLoopService(this, digOutput1, digOutput2);
}


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
void MyApplication::digInput1_OnChange(DigInput *input) {

    if (!input->get())
        digOutput1->pulse(500);
}


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
void MyApplication::digInput2_OnChange(DigInput *input) {

    if (!input->get())
        digOutput2->pulse(500);
}


/// --------------------------------------------------------------------
/// \brief Procesa el event OnChange.
/// \param input: La entrada que ha produit l'event.
///
void MyApplication::digInput3_OnChange(DigInput *input) {

    if (!input->get())
        digOutput3->pulse(500);
}


/// ---------------------------------------------------------------------
/// \brief Constructor.
/// \param application: Aplicacio a la que pertany el servei.
/// \param output: Sortida a controlar.
///
LedLoopService::LedLoopService(
    Application* application,
    DigOutput* output1,
    DigOutput *output2):

    AppLoopService(application),
    output1(output1),
    output2(output2) {
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio.
///
void LedLoopService::onLoop() {

	while (true) {
        output1->pulse(500);
        output2->delayedPulse(125, 250);
		Task::delay(1000);
	}
}


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void AppMain() {

	Application *app = new MyApplication();
	app->execute();
	delete app;
}
