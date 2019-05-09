#include "eos.h"
#include "eosAssert.h"
#include "System/eosApplicationImpl.h"
#include "Services/eosService.h"


using namespace eos;

    
/// ----------------------------------------------------------------------
/// \brief Constructor.
///
Application::Impl::Impl() {
    
}    


/// ----------------------------------------------------------------------
/// \brief Afegeix un servei a l'aplicacio.
/// \param pService: El servei a afeigir.
///
void Application::Impl::addService(
    Service *pService) {    
    
    // Precondicions
    //
    eosAssert(pService != nullptr);

    // Afegeix l'objecte a la llista
    //
    services.add(pService);
}


/// ----------------------------------------------------------------------
/// \brief Elimina un servei de l'aplicacio.
/// \param pService: El servei a eliminar.
///
void Application::Impl::removeService(
    Service *pService) {    

    // Precondicions
    //
    eosAssert(pService != nullptr);

    // Elimina l'objecte de la llista
    //
    services.remove(pService);
}


/// ----------------------------------------------------------------------
/// \brief Elimina tots els serveis de la llista
///
void Application::Impl::removeServices() {

    // Elimina el primer element de la llista mentre no estigui buida.
    //
    while (!services.isEmpty())
        removeService(services.getFront());
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza els serveis.
///
void Application::Impl::initializeServices() {

    // Inicialitza els serveis de la llista, un a un.
    //
    for (ServiceListIterator it(services); it.hasNext(); it.next())
        it.current()->initialize();
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei.
///
void Application::Impl::runServices() {

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
