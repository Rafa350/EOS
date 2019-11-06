#include "eos.h"
#include "Services/eosI2CMasterService.h"
#include "appDisplayService.h"

#include "DSP04Messages.h"

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
    
    I2CMasterTransactionConfiguration transactionConfig;
    transactionConfig.addr = DSP_ADDRESS;
    transactionConfig.protocol = I2CProtocolType::packed;
    transactionConfig.rxBuffer = nullptr;
    transactionConfig.rxSize = 0;
        
    dspDrawShapeMessage msg;
    msg.cmd = DSP_CMD_DRAWSHAPE;
    msg.shape = DRAWSHAPE_ELLIPSE;
    msg.framed = 1;
    msg.filled = 0;
    msg.frameColor = 0xFF;
    msg.fillColor = 0xFF;
    msg.x1 = 10;
    msg.y1 = 10;
    msg.x2 = 30;
    msg.y2 = 30;
    
    transactionConfig.txBuffer = (uint8_t*) &msg;
    transactionConfig.txCount = sizeof(msg);
    I2CMasterTransaction *transaction1 = new I2CMasterTransaction(transactionConfig, nullptr);
    i2cMasterService->startTransaction(transaction1, -1);    
    
    dspRefreshMessage msg2;
    msg.cmd = DSP_CMD_REFRESH;

    transactionConfig.txBuffer = (uint8_t*) &msg2;
    transactionConfig.txCount = sizeof(msg2);
    I2CMasterTransaction *transaction2 = new I2CMasterTransaction(transactionConfig, nullptr);
    i2cMasterService->startTransaction(transaction2, -1);      
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void DisplayService::onLoop() {
    
}


