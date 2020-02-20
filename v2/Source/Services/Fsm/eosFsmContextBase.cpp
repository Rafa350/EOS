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


/// ---------------------------------------------------------------------
/// \brief    Obte l'estat actual.
/// \return   L'estat.
///
FsmStateBase* FsmContextBase::getState() const {
    
    return state;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el nou estat al context.
/// \param    state: El nou estat.
/// \remarks  Crida al metode 'enter' del estat.
///
void FsmContextBase::setState(
    FsmStateBase* state) {

    if (this->state != state) {
        this->state = state;
        if (state != nullptr)
            state->enter();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el estat null.
/// \remarks  Crida al metode 'exit' del estat.
///
void FsmContextBase::clearState() {
    
    if (state != nullptr) {
        state->exit();
        state = nullptr;
    }
}