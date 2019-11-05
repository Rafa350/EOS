#include "eos.h"
#include "HAL/halI2C.h"
#include "Services/eosI2CMasterService.h"
#include "System/Core/eosTask.h"
#include "appApplication.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief Constructor del objecte.
///
MyApplication::MyApplication() {
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza l'aplicacio.
///
void MyApplication::onInitialize() {
    
    I2CMasterServiceConfiguration init = {
        .serviceConfiguration = {
            .serviceName = "I2CmasterService",
            .stackSize = 512,
            .priority = TaskPriority::normal
        },
        .module = HAL_I2C_I2C1
    };
    
    i2cMasterService = new I2CMasterService(this, init);
}
