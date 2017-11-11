#include "System/eosApplication.h"
#include "Services/eosAppLoop.h"
#include "Services/eosDigOutput.h"
#include "Services/eosDigInput.h"
#include "Services/eosExtInterrupt.h"
#include "hal/halGPIO.h"


using namespace eos;


class LedLoopService: public AppLoopService {
    private:
        DigOutput *output1;
        DigOutput *output2;
        
	public:
		LedLoopService(Application *application, DigOutput *output1, DigOutput *output2);
	
    protected:
		void onRun();
};


class MyApplication: public Application {
    private:
        DigInputService *digInputSvc;
        DigInput *digInput1;
        DigOutputService *digOutputSrv;
        DigOutput *digOutput1;
        DigOutput *digOutput2;
        DigOutput *digOutput3;
        ExtInterruptService *extInterruptSvc;
        ExtInterrupt *extInterrupt;
	
    public:
		MyApplication();
        void digInput3_OnChange(DigInput *input);
};


/// ----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {
    
    // Prepara el servei d'entrades digitals
    //
    digInputSvc = new DigInputService(this, nullptr);
    
    DigInputInitializeInfo inputInfo;
    
    inputInfo.port = SW_SW3_PORT;
    inputInfo.pin = SW_SW3_PIN;
    digInput1 = new DigInput(digInputSvc, &inputInfo);
    digInput1->setChangeEvent<MyApplication>(this, &MyApplication::digInput3_OnChange);

    // Prepara el servei de sortides digitals
    //
    digOutputSrv = new DigOutputService(this, nullptr);

    DigOutputInitializeInfo outputInfo;
    outputInfo.openDrain = false;
    outputInfo.initState = false;
    
    outputInfo.port = LEDS_LD1_PORT;
    outputInfo.pin = LEDS_LD1_PIN;
    digOutput1 = new DigOutput(digOutputSrv, &outputInfo);
    
    outputInfo.port = LEDS_LD2_PORT;
    outputInfo.pin = LEDS_LD2_PIN;
    digOutput2 = new DigOutput(digOutputSrv, &outputInfo);
    
    outputInfo.port = LEDS_LD3_PORT;
    outputInfo.pin = LEDS_LD3_PIN;
    digOutput3 = new DigOutput(digOutputSrv, &outputInfo);
    
    //extInterruptSvc = new ExtInterruptService(this);
    //extInterrupt = new ExtInterrupt(extInterruptSvc, HAL_CN_PIN_19);
    
    // Prepara el servei de l'aplicacio
    //
    new LedLoopService(this, digOutput1, digOutput2);
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
/// \brief Bucle principal del proces de control de la sortida.
///
void LedLoopService::onRun() {

	while (true) {
        output1->toggle();
        output2->pulse(300);
		Task::delay(500);
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
