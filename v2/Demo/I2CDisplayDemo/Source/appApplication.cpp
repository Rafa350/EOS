#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxDisplay.h"
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

    I2CMasterService::Configuration cfg = {
        .channel = eosI2CMasterService_I2CModule, 
        .baudRate = eosI2CMasterService_I2CBaudRate        
    };
    i2cMasterService = new I2CMasterService(this, cfg);
    
    // Crea el servei de gestio de display
    //
    GfxDisplay *display = new GfxDisplay(i2cMasterService, 0x62);
    displayService = new DisplayService(this, display);
    
    // Crea el sercei de gestio dels leds
    //
    ledService = new LedService(this);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {
       
}
