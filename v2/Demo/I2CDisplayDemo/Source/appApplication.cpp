#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxDisplay.h"
#include "HAL/halI2C.h"
#include "Services/eosI2CMasterService.h"
#include "System/Core/eosTask.h"
#include "appApplication.h"
#include "appDisplayService.h"
#include "appLedService.h"
#include "HAL/PIC32/halI2C.h"


using namespace eos;
using namespace app;


I2CData channel;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
MyApplication::MyApplication() {

    I2CMasterInitializeInfo i2cInit;
    i2cInit.channel = HAL_I2C_CHANNEL_1;
    i2cInit.baudRate = 100000;
    halI2CMasterInitialize(&channel, &i2cInit);

    I2CMasterService::Configuration cfg;
    cfg.hChannel = &channel;
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
