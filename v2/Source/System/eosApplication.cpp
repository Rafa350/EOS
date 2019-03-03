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

    while (!services.isEmpty())
        removeService(services.getFront());
}


/// ----------------------------------------------------------------------
/// \brief Executa l'aplicacio.
///
void Application::run() {

    // Notifica la inicialitzacio de l'aplicacio.
    //
    onInitialize();

    // Inicialitzacio tots els serveis.
    //
    for (ServiceListIterator it(services); it.hasNext(); it.next())
        it.current()->initialize();

    /// Notifica l'execucio de l'aplicacio
    //
    onRun();

    // Activa el planificador. Aqui comencen a executarse els
    // serveis planificats
    //
    Task::startAll();

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
/// \brief Afegeix un servei a l'aplicacio.
/// \param pService: El servei a afeigir.
///
void Application::addService(
    Service *pService) {

    eosArgumentIsNotNull(pService);

    eosAssert(pService != nullptr);
    eosAssert(pService->pApplication == nullptr);

    pService->pApplication = this;
    services.add(pService);
}


/// ----------------------------------------------------------------------
/// \brief Elimina un servei de l'aplicacio
/// \param pService: El servei a eliminar.
///
void Application::removeService(
    Service *pService) {

    eosArgumentIsNotNull(pService);

    eosAssert(pService != nullptr);
    eosAssert(pService->pApplication == this);

    services.remove(pService);
    pService->pApplication = nullptr;
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


/// ----------------------------------------------------------------------
/// \brief Notificacio de l'execucio de l'aplicacio.
///
void Application::onRun() {

}
