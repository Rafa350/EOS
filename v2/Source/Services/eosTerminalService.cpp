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
    const Settings &settings):

    Service(application),
    hUART(settings.hUART) {

}


/// ----------------------------------------------------------------------
/// \brief    Desructor del objecte.
///
TerminalService::~TerminalService() {

    deinitializeHardware();
}


void TerminalService::deinitializeHardware() {

}


void TerminalService::onInitialize() {

}


void TerminalService::onTask(
    Task *task) {

}