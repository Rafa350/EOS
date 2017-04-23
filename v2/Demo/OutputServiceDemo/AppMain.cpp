#include "System/eosApplication.h"
#include "Services/eosAppLoop.h"
#include "Services/eosDigOutput.h"
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
        DigOutputService *digOutputSrv;
        DigOutput *digOutput1;
        DigOutput *digOutput2;
	
    public:
		MyApplication();
};


/// ----------------------------------------------------------------------
/// \brief Contructor
///
MyApplication::MyApplication() {
   
    digOutputSrv = new DigOutputService(this);
    digOutput1 = new DigOutput(digOutputSrv, LEDS_LD1_PORT, LEDS_LD1_PIN);
    digOutput2 = new DigOutput(digOutputSrv, LEDS_LD2_PORT, LEDS_LD2_PIN);
    
    new LedLoopService(this, digOutput1, digOutput2);
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
        output2->pulse(500);
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
