#include "eos.h"
#include "Services/Fsm/eosFsmContextBase.h"
#include "Services/Fsm/eosFsmStateBase.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
///
FsmContextBase::FsmContextBase():
    state(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el nou estat al context.
/// \param    state: El nou estat.
///
void FsmContextBase::setState(
    FsmStateBase* state) {

    this->state = state;
}
