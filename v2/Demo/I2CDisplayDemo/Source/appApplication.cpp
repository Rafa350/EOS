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


I2CData i2cData;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
MyApplication::MyApplication() {

    I2CMasterSettings i2cSettings;
    i2cSettings.channel = HAL_I2C_CHANNEL_1;
    i2cSettings.baudRate = 100000;
    I2CHandler hI2C = halI2CMasterInitialize(&i2cData, &i2cSettings);

    I2CMasterService::Settings i2cMasterServiceSettings;
    i2cMasterServiceSettings.hI2C = hI2C;
    i2cMasterService = new I2CMasterService(this, i2cMasterServiceSettings);

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
