#include "eos.h"
#include "Services/Fsm/eosFsmContextBase.h"
#include "Services/Fsm/eosFsmStateBase.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    context: El context.
///
FsmStateBase::FsmStateBase(
    FsmContextBase* context):

    context(context) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
FsmStateBase::~FsmStateBase() {
    
}