#include "eos.h"
#include "Services/eosFsmService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief   Constructor.
/// \param   application: Aplicacio on afeigir el servei.
/// \param   sm: La maquina d'estat a procesar.
///
FsmService::FsmService(
    Application* application,
    StateMachine* sm):

    Service(application),
    sm(sm),
    eventCallback(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void FsmService::onTask() {

    while (true) {
        sm->task();
    }
}
