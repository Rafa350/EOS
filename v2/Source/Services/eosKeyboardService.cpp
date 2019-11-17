#include "eos.h"
#include "Services/eosKeyboardService.h"
#include "Services/eosI2CMasterService.h"
#include "../../../MD-KBD01/KBD01Messages.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor per defecte.
///
KeyboardService::Configuration::Configuration() {

	i2cAddress = 0;
	i2cService = nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param 	  application: Aplicacio a la que pertany.
/// \param    cfg: Parametres de configuracio.
///
KeyboardService::KeyboardService(
    Application *application,
	const Configuration *cfg) :
    
    Service(application),
    state(0),
    eventCallback(nullptr) {

	if (cfg != nullptr)
		this->cfg = *cfg;
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
