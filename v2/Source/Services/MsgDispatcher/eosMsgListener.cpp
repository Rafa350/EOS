#include "eos.h"
#include "Services/MsgDispatcher/eosMsgDispatcherService.h"


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    typeId: Identificador del tipus de missatge.
///
eos::MsgListener::MsgListener(
	uint32_t typeId) :
	_typeId {typeId} {

}

