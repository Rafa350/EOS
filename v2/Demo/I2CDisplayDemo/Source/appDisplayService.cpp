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
        
    dspDrawShapeMessage msg1;
    msg1.cmd = DSP_CMD_DRAWSHAPE;
    msg1.shape = DRAWSHAPE_ELLIPSE;
    msg1.framed = 1;
    msg1.filled = 0;
    msg1.frameColor = 0xFF;
    msg1.fillColor = 0xFF;
    msg1.x1 = 10;
    msg1.y1 = 10;
    msg1.x2 = 30;
    msg1.y2 = 30;
    
    I2CMasterTransaction *transaction1 = new I2CMasterTransaction(
        DSP_ADDRESS,
        I2CProtocolType::packed,
        (uint8_t*) &msg1, 
        sizeof(msg1),
        nullptr);
    i2cMasterService->startTransaction(transaction1, -1);    
    
    dspRefreshMessage msg2;
    msg2.cmd = DSP_CMD_REFRESH;

    I2CMasterTransaction *transaction2 = new I2CMasterTransaction(
        DSP_ADDRESS,
        I2CProtocolType::packed,
        (uint8_t*) &msg2, 
        sizeof(msg2),
        nullptr);
    i2cMasterService->startTransaction(transaction2, -1);      
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void DisplayService::onLoop() {
    
}


