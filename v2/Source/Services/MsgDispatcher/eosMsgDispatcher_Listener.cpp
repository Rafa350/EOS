module;


#include "eos.h"


module Eos.Services.MsgDispatcher;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    typeId: Identificador del tipus de missatge.
///
eos::MsgListener::MsgListener(
	uint32_t typeId) :
	_typeId {typeId} {

}

