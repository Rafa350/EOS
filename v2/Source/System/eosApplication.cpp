#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Application::Application():

	_initialized(false),
    _taskEventCallback(*this, &Application::taskEventHandler)
#if Eos_ApplicationTickEnabled
    ,timerEventCallback(this, &Application::timerEventHandler),
    timer(true, &timerEventCallback, this)
#endif
{
}


/// ----------------------------------------------------------------------
/// \brief    Destructor. Si conte serveis, els elimina de la llista.
///
Application::~Application() {
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el event d'inici de la tasca del servei.
/// \param    args: Parametres del event.
///
void Application::taskEventHandler(
    const Task::EventArgs &args) {

    Service *service = static_cast<Service*>(args.params);
    if (service != nullptr)
        service->task();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el event del temporitzador TICK.
/// \param    args: Parametres del event.
///
#if Eos_ApplicationTickEnabled
void Application::timerEventHandler(
    const Timer::EventArgs &args) {

    tick();
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Executa l'aplicacio.
///
void Application::run() {

	_initialized = true;

    // Notifica la inicialitzacio de l'aplicacio.
    //
    onInitialize();

    // Inicialitzacio tots els serveis.
    //
    initializeServices();

    // Executa els serveis fins que finalitzi l'aplicacio.
    //
    runServices();

    // Finalitza tots els serveis
    //
    terminateServices();

    // Notifica el final de l'aplicacio.
    //
    onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la senyal tick del sistema
///
#if Eos_ApplicationTickEnabled
void Application::tick() {

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
void Application::initializeServices() {

    // Inicialitza els serveis de la llista, un a un.
    //
    for (auto si: _serviceInfoList)
        si->service->initialize();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza els serveis.
///
void Application::terminateServices() {

    // Finalitza els serveis de la llista, un a un.
    //
    for (auto si: _serviceInfoList)
  		si->service->terminate();
}


/// ----------------------------------------------------------------------
/// \brief    Posa els serveix en en execucio.
///
void Application::runServices() {

    // Inicialitza el temporitzador tick
    //
#if Eos_ApplicationTickEnabled
    timer.start(APPLICATION_TICK_PERIOD, 0);
#endif

    // Crea una tasca per executar cada servei
    //
    for (auto si: _serviceInfoList) {
    	if (si->service->getState() == Service::State::ready) {
			si->task = new Task(
				si->stackSize,
				si->priority,
				si->name ? si->name : "SERVICE",
				&_taskEventCallback,
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
void Application::addService(
	Service *service,
	Task::Priority priority,
	unsigned stackSize,
	const char *name) {

	eosAssert(service != nullptr);

	ServiceInfo *si = new ServiceInfo;
	eosAssert(si != nullptr);

	si->service = service;
	si->priority = priority;
	si->stackSize = stackSize;
	si->name = name;
	si->task = nullptr;

	_serviceInfoList.pushBack(si);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un servei de l'aplicacio
/// \param    service: El servei a eliminar.
///
void Application::removeService(
    Service *service) {

    eosAssert(service != nullptr);

    for (auto si: _serviceInfoList) {
    	if (si->service == service) {
        	_serviceInfoList.remove(si);
    		break;
    	}
    }
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots els serveis de l'aplicacio.
///
void Application::removeServices() {

	_serviceInfoList.clear();
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio de la initcialitzacio de l'aplicacio.
///
void Application::onInitialize() {

#if Eos_UseApplicationInitializeCallback
    if (initializeEventCallback != nullptr)
	    initializeEventCallback->execute(this);
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio la finalitzacio de l'aplicacio.
///
void Application::onTerminate() {

#if Eos_UseApplicationTerminateCallback
	if (terminateEventCallback != nullptr)
	    terminateEventCallback->execute(this);
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio del senyal tick
///
#if Eos_ApplicationTickEnabled
void Application::onTick() {

}
#endif
