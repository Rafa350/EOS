#include "eos.h"
#include "Services/eosDigOutputService.h"
#include "Services/eosDigInputService.h"
#include "appApplication.h"
#include "appLedLoopService.h"


using namespace eos;
using namespace app;


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
