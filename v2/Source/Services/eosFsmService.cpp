#include "eos.h"
#include "Services/eosFsmService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief   Constructor.
/// \param   application: Aplicacio on afeigir el servei.
/// \param   sm: La maquina d'estat a procesar.
///
FsmService::FsmService(
    Application* application) :

    Service(application),
    eventCallback(nullptr) {

}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una maquina al servei.
/// \param    machine: La maquina a afeigir.
///
void FsmService::addMachine(
    FsmMachine *machine) {
    
    eosAssert(machine != nullptr);
    eosAssert(machine->service == nullptr);

    machines.pushBack(machine);
    machine->service = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina una maquina del servei.
/// \param    machine: La maquina a eliminar.
///
void FsmService::removeMachine(
    FsmMachine* machine) {

    eosAssert(machine != nullptr);
    eosAssert(machine->service == this);

    machines.removeAt(machines.indexOf(machine));
    machine->service = nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el servei.
/// 
void FsmService::onInitialize() {

    for (auto it = machines.begin(); it != machines.end(); it++) {
        FsmMachine* machine = *it;
        machine->initialize();
    }    
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void FsmService::onTask() {

    while (true) {
        for (auto it = machines.begin(); it != machines.end(); it++) {
            FsmMachine* machine = *it;
            machine->task();
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief   Constructor.
///
FsmMachine::FsmMachine() :
    service(nullptr) {
    
}