#include "eos.h"
#include "Services/eosI2CMasterService.h"
#include "appDisplayService.h"


using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    application: Applicacio a la que pertany el servei.
/// \param    i2cMasterService: El servei de comunicacio i2c.
///
DisplayService::DisplayService(
    Application *application,
    I2CMasterService *i2cMasterService):
    
    AppLoopService(application),
    i2cMasterService(i2cMasterService) {
    
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio
/// \remarks  S'executa d'ins del planificador.
///
void DisplayService::onSetup() {
    
    transactionConfig.addr = 0;
    transactionConfig.txBuffer = txBuffer;
    transactionConfig.txCount = 0;
    transactionConfig.rxBuffer = rxBuffer;
    transactionConfig.rxSize = sizeof(rxBuffer);
    transactionConfig.protocol = I2CProtocolType::packed;
    
    I2CMasterTransaction *transaction = new I2CMasterTransaction(transactionConfig, nullptr);
    i2cMasterService->startTransaction(transaction, -1);    
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void DisplayService::onLoop() {
    
}


