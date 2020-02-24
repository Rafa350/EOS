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


/// ---------------------------------------------------------------------
/// \brief    Inicialitza la maquina d'estats.
/// \param    state: El estat inicial.
/// \remarks  CRida al metode 'enter' del estat seleccionat.
///
void FsmContextBase::initialize(
    FsmStateBase *state) {
    
    if (state != nullptr) {
        this->state = state;
        state->enter();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Es crida al final de la transicio per seleccionar el 
///           nou estat.
/// \param    state: El nou estat.
/// \remarks  Crida al metode 'enter' del nou estat i el selecciona.
///
void FsmContextBase::endTransition(
    FsmStateBase* state) {

    if (this->state != state) {
        this->state = state;
        if (state != nullptr)
            state->enter();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Es crida al inici de la transicio.
/// \remarks  Crida al metode 'exit' del estat.
///
void FsmContextBase::beginTransition() {
    
    if (state != nullptr) {
        state->exit();
        state = nullptr;
    }
}