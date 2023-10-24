#include "eos.h"
#include "Services/eosFsmService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief   Constructor.
///
FsmService::FsmService() :

    _event {nullptr},
    _eventEnabled {false} {

}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una maquina al servei.
/// \param    machine: La maquina a afeigir.
///
void FsmService::addMachine(
    FsmMachine *machine) {

    eosAssert(machine != nullptr);
    eosAssert(machine->_service == nullptr);

    _machines.pushBack(machine);
    machine->_service = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una maquina del servei.
/// \param    machine: La maquina a eliminar.
///
void FsmService::removeMachine(
    FsmMachine* machine) {

    eosAssert(machine != nullptr);
    eosAssert(machine->_service == this);

    _machines.remove(machine);
    machine->_service = nullptr;
}


void FsmService::setEvent(
    IEvent &event,
    bool enabled) {

    _event = &event;
    _eventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
///
void FsmService::onInitialize() {

    for (auto machine: _machines)
        machine->initialize();
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void FsmService::onTask() {

    // Repeteix indefinidament
    //
    while (true) {
        
        for (auto machine: _machines)
            machine->task();
    }
}


/// ----------------------------------------------------------------------
/// \brief   Constructor.
///
FsmMachine::FsmMachine() :
    _service(nullptr) {

}
