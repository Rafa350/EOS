#include "eos.h"
#include "HAL/halI2C.h"
#include "Services/eosI2CMasterService.h"
#include "System/Core/eosTask.h"
#include "appApplication.h"
#include "appDisplayService.h"
#include "appLedService.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
MyApplication::MyApplication() {

    i2cMasterService = new I2CMasterService(this, nullptr);
    
    // Crea el servei de gestio de display
    //
    displayService = new DisplayService(this, i2cMasterService);
    
    // Crea el sercei de gestio dels leds
    //
    ledService = new LedService(this);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {
       
}
