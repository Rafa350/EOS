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
    _taskEventCallback(this, &Application::taskEventHandler)
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

	// Destrueix els serveis de la llista. El contenidor ja els
	// destrueix automaticament
	//
	while (!_services.isEmpty())
		delete _services.peekFront();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el event d'inici de la tasca del servei.
/// \param    args: Parametres del event.
///
void Application::taskEventHandler(
    const Task::EventArgs& args) {

    Service* service = static_cast<Service*>(args.params);
    if (service != nullptr)
        while (true)
            service->task(args.task);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el event del temporitzador TICK.
/// \param    args: Parametres del event.
///
#if Eos_ApplicationTickEnabled
void Application::timerEventHandler(
    const Timer::EventArgs& args) {

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

    // Executa els serveis fins que acavi l'aplicacio.
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
    for (auto it = services.begin(); it != services.end(); it++) {
        Service* service = *it;
		service->tick();
    }
}
#endif


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els serveis.
///
void Application::initializeServices() {

    // Inicialitza els serveis de la llista, un a un.
    //
    for (auto service: _services)
        service->initialize();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza els serveis.
///
void Application::terminateServices() {

    // Finalitza els serveis de la llista, un a un.
    //
    for (auto service: _services)
        service->terminate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les tasques del servei.
///
void Application::runServices() {

#if  1 //def USE_SCHEDULER

    // Inicialitza el terporitzador tick
    //
#if Eos_ApplicationTickEnabled
    timer.start(APPLICATION_TICK_PERIOD, 0);
#endif

    // Crea una tasca per executar cada servei
    //
    for (auto service: _services) {
        Task* task = new Task(
            service->getStackSize(),
            service->getPriority(),
            service->getName(),
            &_taskEventCallback,
            static_cast<void*>(service));
        _tasks.pushBack(task);
    }

    // Executa les tasques
    //
    Task::startAll();

#else
    bool done = false;
    while (!done) {

        // Executa la tasca de cada servei, un a un
        //
    	for (auto service: _services)
    		service->task();
    }
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un servei a l'aplicacio.
/// \param    service: El servei a afeigir.
///
void Application::addService(
    Service* service) {

    eosAssert(service != nullptr);

    eos::link(this, service);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un servei de l'aplicacio
/// \param    service: El servei a eliminar.
///
void Application::removeService(
    Service* service) {

    eosAssert(service != nullptr);

    eos::unlink(this, service);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots els serveis de l'aplicacio.
///
void Application::removeServices() {

	while (!_services.isEmpty())
        removeService(_services.peekFront());
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


/// ----------------------------------------------------------------------
/// \brief    Afegeix el servei a la llista de serveis
/// \param    application: L'aplicacio.
/// \param    service: El servei.
///
void eos::link(
	Application* application,
	Service* service) {

	eosAssert(application != nullptr);
    eosAssert(service->_application == nullptr);

    application->_services.pushBack(service);
    service->_application = application;
}


/// ----------------------------------------------------------------------
/// \brief    Treu el servei de la llista de serveis.
/// \param    application: L'aplicacio.
/// \param    service: El servei.
///
void eos::unlink(
	Application* application,
	Service* service) {

	eosAssert(application != nullptr);
    eosAssert(service->_application == application);

    service->_application = nullptr;
    application->_services.removeAt(application->_services.indexOf(service));
}
