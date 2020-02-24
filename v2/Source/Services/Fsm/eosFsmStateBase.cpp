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


/// ----------------------------------------------------------------------
/// \brief    Inicia el process de canvi d'estat d'ins d'una transicio.
///
void FsmStateBase::beginTransition() {
    
    context->beginTransition();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el proces de canvi d'estat dins d'una transicio.
/// \param    state: El nou estat.
///
void FsmStateBase::endTransition(
    FsmStateBase* state) {
    
    context->endTransition(state);
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el proces de canvi d'estat dins d'una transicio.
/// \param    state: El nou estat.
///
void FsmStateBase::endTransitionPush(
    FsmStateBase* state) {
    
    context->endTransitionPush(state);
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el proces de canvi d'estat dins d'una transicio.
///
void FsmStateBase::endTransitionPop() {
    
    context->endTransitionPop();
}
