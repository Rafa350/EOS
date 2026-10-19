module Eos.Services.MsgDispatcher;


import Eos.Types;


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    typeId: Identificador del tipus de missatge.
///
MsgListener::MsgListener(
	UInt32 typeId) :
	_typeId {typeId} {

}
