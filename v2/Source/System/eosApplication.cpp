#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"
#include "System/eosApplication.h"
#include "string.h"


using namespace eos;

static Application *application = nullptr;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Application::Application() {

	eosAssert(application == nullptr);

    application = this;
}


/// ----------------------------------------------------------------------
/// \brief    Destructor. Si conte serveis, els elimina de la llista.
///
Application::~Application() {

    while (!services.isEmpty()) {

    	Service *service = services.getFront();
    	services.remove(service);

    	delete service;
    }
}


/// ---------------------------------------------------------------------
/// \brief Obte la instancia de l'aplicacio.
/// \return L'aplicacio.
///
Application *Application::getApplication() {

	return application;
}


/// ----------------------------------------------------------------------
/// \brief    Executa l'aplicacio.
///
void Application::run() {

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
    for (ServiceListIterator it(services); it.hasNext(); it.next())
        it.current()->tick();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els serveis.
///
void Application::initializeServices() {

    // Inicialitza els serveis de la llista, un a un.
    //
    for (ServiceListIterator it(services); it.hasNext(); it.next())
        it.current()->initialize();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les tasques del servei.
///
void Application::runServices() {

#if  1 //def USE_SCHEDULER
    Task::startAll();

#else
    bool done = false;
    while (!done) {

        // Executa la tasca de cada servei, un a un
        //
    	for (ServiceListIterator it(services); it.hasNext(); it.next())
    		it.current()->task();
    }
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un servei a l'aplicacio.
/// \param    service: El servei a afeigir.
///
void Application::addService(
    Service *service) {

    // Precondicions
    //
    eosAssert(service != nullptr);
    eosAssert(service->application == nullptr);

    /// Afegeix el servei
    //
    services.add(service);
    service->application = this;
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un servei de l'aplicacio
/// \param    service: El servei a eliminar.
///
void Application::removeService(
    Service *service) {

    // Precondicions
    //
    eosAssert(service != nullptr);
    eosAssert(service->application == this);

    // Elimina el servei
    //
    service->application = nullptr;
    services.remove(service);
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots els serveis de l'aplicacio.
///
void Application::removeServices() {

    while (!services.isEmpty())
        removeService(services.getFront());
}


/// ----------------------------------------------------------------------
/// \brief    Obte el servei especificat.
/// \param    id: El identificador del servei.
/// \return   El servei, null si no el troba.
///
Service *Application::getService(
    int id) const {

  	for (ServiceListIterator it(services); it.hasNext(); it.next()) {
   		Service *service = it.current();
        if (service->getId() == id)
            return service;
    }

    return nullptr;
}


/// ---------------------------------------------------------------------
/// \brief    Obte el servei especificat.
/// \param    name: El nom del servei.
/// \return   El servei, null si no el troba.
///
Service *Application::getService(
    const String& name) const {

  	for (ServiceListIterator it(services); it.hasNext(); it.next()) {
   		Service *service = it.current();
        if (service->getName() == name)
            return service;
    }

    return nullptr;
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

