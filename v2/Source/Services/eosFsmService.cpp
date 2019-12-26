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
    eventQueue(10),
    eventCallback(nullptr),
    actionCallback(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void FsmService::onTask() {

    while (true) {

        Event event;

        if (eventQueue.get(event, unsigned(-1))) {
            if (eventCallback != nullptr) {
                EventArgs args;
                args.service = this;
                eventCallback->execute(args);
            }
            //sm->acceptEvent(event);
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Envia un event a la maquina d'estats pel seu procesament.
///
bool FsmService::acceptEvent(
    Event event,
    unsigned timeout) {

    return eventQueue.put(event, timeout);
}
