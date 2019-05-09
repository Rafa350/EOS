#include "eos.h"
#include "Services/eosService.h"


using namespace eos;


class Application::Impl {

    private:
        typedef List<Service*> ServiceList;
        typedef ListIterator<Service*> ServiceListIterator;

    private:
        ServiceList services;

    public:
        Impl();

        void initializeServices();
        void runServices();

        void addService(Service *pService);       
        void removeService(Service *pService);
        void removeServices();    
};   
    
    
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

    services.add(pService);
}


/// ----------------------------------------------------------------------
/// \brief Elimina un servei de l'aplicacio.
/// \param pService: El servei a eliminar.
///
void Application::Impl::removeService(
    Service *pService) {    

    services.remove(pService);
}


/// ----------------------------------------------------------------------
/// \brief Elimina tots els serveis de la llista
///
void Application::Impl::removeServices() {

    while (!services.isEmpty())
        removeService(services.getFront());
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza els serveis.
///
void Application::Impl::initializeServices() {

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
    while (true) {
    	for (ServiceListIterator it(services); it.hasNext(); it.next())
    		it.current()->task();
    }
#endif
    
}
