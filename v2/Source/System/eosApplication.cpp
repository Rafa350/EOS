#include "eos.h"
#include "eosAssert.h"
#include "System/eosApplication.h"
#include "System/eosApplicationImpl.h"
#include "Services/eosService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
Application::Application():

    pImpl(new Impl()) {

    // Precondicions
    //
    eosAssert(pImpl == nullptr);
}


/// ----------------------------------------------------------------------
/// \brief Destructor. Si conte serveis, els elimina de la llista.
///
Application::~Application() {
    
    // Precondicions
    //
    eosAssert(pImpl != nullptr);

    // Elimina tots els serveis
    //
    pImpl->removeServices();
    
    delete pImpl;
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
    pImpl->initializeServices();
    
    // Executa els serveis fins que acavi l'aplicacio.
    //
    pImpl->runServices();

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
    //for (ServiceListIterator it(services); it.hasNext(); it.next())
//        it.current()->tick();
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
    pImpl->addService(pService);
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
    pImpl->removeService(pService);
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

