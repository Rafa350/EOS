#include "eos.h"
#include "eosAssert.h"
#include "System/eosApplication.h"
#include "Services/eosService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
Application::Application() {

}


/// ----------------------------------------------------------------------
/// \brief Destructor. Si conte serveis, els elimina de la llista.
///
Application::~Application() {

    // Elimina tots els serveis
    //
    removeServices();
}


/// ----------------------------------------------------------------------
/// \brief Executa l'aplicacio.
///
void Application::run() {

    // Precondicions
    //
    eosAssert(pImpl != nullptr);

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
/// \brief Procesa la senyal tick del sistema
///
void Application::tick() {

	onTick();

	// Notifica la senyal tick a tots els serveis.
    //
    for (ServiceListIterator it(services); it.hasNext(); it.next())
        it.current()->tick();
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza els serveis.
///
void Application::initializeServices() {

    // Inicialitza els serveis de la llista, un a un.
    //
    for (ServiceListIterator it(services); it.hasNext(); it.next())
        it.current()->initialize();
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei.
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
/// \brief Afegeix un servei a l'aplicacio.
/// \param pService: El servei a afeigir.
///
void Application::addService(
    Service *pService) {

    // Precondicions
    //
    eosAssert(pImpl != nullptr);
    eosAssert(pService != nullptr);

    /// Afegeix el servei
    //
    services.add(pService);
    pService->pApplication = this;
}


/// ----------------------------------------------------------------------
/// \brief Elimina un servei de l'aplicacio
/// \param pService: El servei a eliminar.
///
void Application::removeService(
    Service *pService) {

    // Precondicions
    //
    eosAssert(pImpl != nullptr);
    eosAssert(pService != nullptr);

    // Elimina el servei
    //
    pService->pApplication = nullptr;
    services.remove(pService);
}


/// ----------------------------------------------------------------------
/// \brief Elimina tots els serveis de l'aplicacio.
///
void Application::removeServices() {
    
    while (!services.isEmpty())
        services.removeAt(0);
}


/// ----------------------------------------------------------------------
/// \brief Notificacio de la initcialitzacio de l'aplicacio.
///
void Application::onInitialize() {

	// if (initializeEvent != nullptr)
	//     initializeEvent->execute(this);
}


/// ----------------------------------------------------------------------
/// \brief Notificacio la finalitzacio de l'aplicacio.
///
void Application::onTerminate() {

	// if (terminateEvent != nullptr)
	//     terminateEvent->execute(this);
}


/// ----------------------------------------------------------------------
/// \brief Notificacio del senyal tick
///
void Application::onTick() {

}

