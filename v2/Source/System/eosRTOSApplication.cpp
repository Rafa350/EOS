#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"
#include "System/eosRTOSApplication.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
RTOSApplication::RTOSApplication():

    _taskCallback(*this, &RTOSApplication::taskCallbackHandler)
#if Eos_ApplicationTickEnabled
    ,timerEventCallback(this, &RTOSApplication::timerEventHandler),
    timer(true, &timerEventCallback, this)
#endif
{
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el event d'inici de la tasca del servei.
/// \param    args: Parametres del event.
///
void RTOSApplication::taskCallbackHandler(
    const TaskCallbackArgs &args) {

    auto service = static_cast<Service*>(args.params);
    if (service != nullptr) {
        if (service->taskStart()) {
            while (service->taskRun())
                continue;
        }
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el event del temporitzador TICK.
/// \param    args: Parametres del event.
///
#if Eos_ApplicationTickEnabled
void RTOSApplication::timerEventHandler(
    const Timer::EventArgs &args) {

    tick();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Procesa la senyal tick del sistema
///
#if Eos_ApplicationTickEnabled
void RTOSApplication::tick() {

	onTick();

	// Notifica la senyal tick a tots els serveis.
    //
    for (auto si: _serviceInfoList)
		si->service->tick();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els serveis.
///
void RTOSApplication::initializeServices() {

    // Inicialitza els serveis de la llista, un a un.
    //
    for (auto si: _serviceInfoList)
        si->service->initialize();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza els serveis.
///
void RTOSApplication::terminateServices() {

    // Finalitza els serveis de la llista, un a un.
    //
    for (auto si: _serviceInfoList)
  		si->service->terminate();
}


/// ----------------------------------------------------------------------
/// \brief    Posa els serveix en en execucio.
///
void RTOSApplication::runServices() {

    // Inicialitza el temporitzador tick
    //
#if Eos_ApplicationTickEnabled
    timer.start(APPLICATION_TICK_PERIOD, 0);
#endif

    // Crea una tasca per executar cada servei
    //
    for (auto si: _serviceInfoList) {

        // Comprova si el servei esta inicialitzat
        //
    	if (si->service->getState() == Service::State::initialized) {

    	    // Crea la tasca del servei.
    	    //
			si->task = new Task(
				si->stackSize,
				si->priority,
				si->name ? si->name : "SERVICE",
				&_taskCallback,
				static_cast<void*>(si->service));
    	}
    }

    // Inicia el planificador i executa les tasques. No retorna fins
    // que finalitzon totes les tasques
    //
    Task::startAll();
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un servei a l'aplicacio.
/// \param    service: EL servei.
/// \param    priority: La prioritat.
/// \param    stackSize: Tamany del stack.
/// \param    name: Nom del servei.
///
void RTOSApplication::addService(
	Service *service,
	Task::Priority priority,
	unsigned stackSize,
	const char *name) {

	eosAssert(service != nullptr);

	auto si = new ServiceInfo;
	eosAssert(si != nullptr);

	si->service = service;
	si->priority = priority;
	si->stackSize = stackSize;
	si->name = name;
	si->task = nullptr;

	_serviceInfoList.pushFront(si);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un servei de l'aplicacio
/// \param    service: El servei a eliminar.
///
void RTOSApplication::removeService(
    Service *service) {

    eosAssert(service != nullptr);

    /*for (auto si: _serviceInfoList) {
    	if (si->service == service) {
        	_serviceInfoList.remove(si);
    		break;
    	}
    }*/
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots els serveis de l'aplicacio.
///
void RTOSApplication::removeServices() {

	//_serviceInfoList.clear();
}
