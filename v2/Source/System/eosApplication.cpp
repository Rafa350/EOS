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

	initialized(false),
    taskEventCallback(this, &Application::taskEventHandler) {

}


/// ----------------------------------------------------------------------
/// \brief    Destructor. Si conte serveis, els elimina de la llista.
///
Application::~Application() {

	// Destrueix els serveis de la llista. El contenidor ja es
	// destrueix automaticament
	//
	while (!services.isEmpty())
		delete services.getFirst();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el event d'inici de la tasca del servei.
/// \param    args: Parametres del event.
///
void Application::taskEventHandler(
    const Task::EventArgs &args) {
    
    eosAssert(args.param != nullptr);
    
    Service *service = static_cast<Service*>(args.param);
    while (true)
        service->task();
}


/// ----------------------------------------------------------------------
/// \brief    Executa l'aplicacio.
///
void Application::run() {

	initialized = true;

    // Notifica la inicialitzacio de l'aplicacio.
    //
    onInitialize();

    // Inicialitzacio tots els serveis.
    //
    initializeServices();

    // Executa els serveis fins que acavi l'aplicacio.
    //
    runServices();

    // Notifica el final de l'aplicacio.
    //
    onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la senyal tick del sistema
///
void Application::tick() {

	onTick();

	// Notifica la senyal tick a tots els serveis.
    //
    for (ServiceListIterator it(services); it.hasNext(); it.next()) {
        Service *service = it.getCurrent();
		service->tick();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els serveis.
///
void Application::initializeServices() {

    // Inicialitza els serveis de la llista, un a un.
    //   
    for (ServiceListIterator it(services); it.hasNext(); it.next()) {
        Service *service = it.getCurrent();
        service->initialize();
    }
    
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les tasques del servei.
///
void Application::runServices() {

#if  1 //def USE_SCHEDULER
    
    // Crea una tasca per executar cada servei
    //
    for (ServiceListIterator it(services); it.hasNext(); it.next()) {
        Service *service = it.getCurrent();
        Task *task = new Task(
            service->getStackSize(),
            service->getPriority(),
            service->getName(),
            &taskEventCallback,
            static_cast<void*>(service));
        tasks.add(task);
    }  
    
    // Executa les tasques
    //
    Task::startAll();

#else
    bool done = false;
    while (!done) {

        // Executa la tasca de cada servei, un a un
        //
    	for (auto service: services)
    		service->task();
    }
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un servei a l'aplicacio.
/// \param    service: El servei a afeigir.
///
void Application::addService(
    Service *service) {

    eosAssert(service != nullptr);

    link(this, service);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un servei de l'aplicacio
/// \param    service: El servei a eliminar.
///
void Application::removeService(
    Service *service) {

    eosAssert(service != nullptr);

    unlink(this, service);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots els serveis de l'aplicacio.
///
void Application::removeServices() {

	while (!services.isEmpty())
        removeService(services.getFirst());
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio de la initcialitzacio de l'aplicacio.
///
void Application::onInitialize() {

	// if (initializeEventCallback != nullptr)
	//     initializeEventCallback->execute(this);
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio la finalitzacio de l'aplicacio.
///
void Application::onTerminate() {

	// if (terminateEventCallback != nullptr)
	//     terminateEventCallback->execute(this);
}


/// ----------------------------------------------------------------------
/// \brief    Notificacio del senyal tick
///
void Application::onTick() {

}


/// ----------------------------------------------------------------------
/// \brief    Afegeix el servei a la llista de serveis
/// \param    application: L'aplicacio.
/// \param    service: El servei.
///
void eos::link(
	Application *application,
	Service *service) {

	eosAssert(application != nullptr);
    eosAssert(service->application == nullptr);

    application->services.add(service);
    service->application = application;
}


/// ----------------------------------------------------------------------
/// \brief    Treu el servei de la llista de serveis.
/// \param    application: L'aplicacio.
/// \param    service: El servei.
///
void eos::unlink(
	Application *application,
	Service *service) {

	eosAssert(application != nullptr);
    eosAssert(service->application == application);

    service->application = nullptr;
    application->services.remove(service);
}
