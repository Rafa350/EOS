#include "eos.h"
#include "HAL/halUART.h"
#include "Services/eosTerminalService.h"
#include "HAL/PIC32/halUART.h"



using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    application: Aplicacio a la que afeigir el servei.
/// \param    cfg: Opcions de configuracio.
///
TerminalService::TerminalService(
    Application *application,
    const Configuration *cfg):

    Service(application),
    module(cfg->module),
    baudRate(cfg->baudRate) {
    
}


void TerminalService::onInitialize() {
    
    UARTInitializeInfo info = {
        .module = module,
        .baudRate = baudRate
    };
    halUARTInitialize(&info);
}


void TerminalService::onTask() {
    
}