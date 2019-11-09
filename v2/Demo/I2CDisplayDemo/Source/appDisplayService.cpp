#include "eos.h"
#include "Services/eosI2CMasterService.h"
#include "appDisplayService.h"

#include "DSP04Messages.h"

using namespace eos;
using namespace app;


static void sendData(
    I2CMasterService *service,
    uint8_t *buffer, 
    int count) {

    I2CMasterTransaction *transaction = new I2CMasterTransaction(
        DSP_ADDRESS,
        I2CMasterTransaction::Protocol::packed,
        buffer, 
        count,
        nullptr);

    service->startTransaction(transaction, -1);  
 }



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
    
    dspClearMessage msg1;
    msg1.cmd = DSP_CMD_CLEAR;   
    sendData(i2cMasterService, (uint8_t*) &msg1, sizeof(msg1));
    
    dspDrawTextMessage msg2;
    msg2.cmd = DSP_CMD_DRAWTEXT;
    msg2.color = 0xFF;
    msg2.font = 0xFF;
    msg2.x = 10;
    msg2.y = 10;
    msg2.textLen = 4;
    sendData(i2cMasterService, (uint8_t*) &msg2, sizeof(msg2));
    sendData(i2cMasterService, (uint8_t*) "HOLA", 4);
    
    dspRefreshMessage msg3;
    msg3.cmd = DSP_CMD_REFRESH;
    sendData(i2cMasterService, (uint8_t*) &msg3, sizeof(msg3));
    
    while (true)
        Task::delay(1000);
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void DisplayService::onLoop() {
    
}


