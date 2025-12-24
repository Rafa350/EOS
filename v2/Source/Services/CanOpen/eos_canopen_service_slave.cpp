#include "eos.h"
#include "Services/CanOpen/eos_canopen_service_slave.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    params: Parametres d'inicialitzacio.
///
CanOpenSlaveService::CanOpenSlaveService(
	InitParams const &params):
	CanOpenService(params) {

}
