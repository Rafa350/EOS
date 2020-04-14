#include "eos.h"
#include "Services/eosKeyboardService.h"
#include "Services/eosI2CMasterService.h"
#include "../../../MD-KBD01/KBD01Messages.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param 	  application: Aplicacio a la que pertany.
/// \param    cfg: Parametres de configuracio.
///
KeyboardService::KeyboardService(
    Application* application,
	I2CMasterService* i2cService,
	int i2cAddress) :
    
    Service(application),
	i2cAddress(i2cAddress),
	i2cService(i2cService),
    state(0),
    eventCallback(nullptr) {

}


/// ---------------------------------------------------------------------
/// \brief    Inicialitzacio abans del planificador.
///
void KeyboardService::onInitialize() {

}


/// ----------------------------------------------------------------------
/// \brief    Procesa les tasques del servei
///
void KeyboardService::onTask() {
    
	if (eventCallback != nullptr) {

	}
}
