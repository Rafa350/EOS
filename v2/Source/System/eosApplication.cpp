#include "eosAssert.h"
#include "System/eosApplication.h"
#include "Services/eosService.h"
#include "HAL/halSYS.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
Application::Application() {

    halSYSInitialize();
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
Application::~Application() {

    while (services.getCount() > 0)
        removeService(services[0]);
}


/// ----------------------------------------------------------------------
/// \brief Executa l'aplicacio.
///
void Application::execute() {

    onInitialize();
    Task::startAll();
    onTerminate();
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un servei a l'aplicacio.
/// \param service: El servei a afeigir.
///
void Application::addService(
    Service *service) {

    eosArgumentIsNotNull(service);

    if ((service != nullptr) && (service->application == nullptr)) {
        service->application = this;
        services.add(service);
    }
}


/// ----------------------------------------------------------------------
/// \brief Elimina un servei de l'aplicacio
/// \param service: El servei a eliminar.
///
void Application::removeService(
    Service *service) {

    eosArgumentIsNotNull(service);

    if ((service != nullptr) && (service->application == this)) {
        services.remove(services.indexOf(service));
        service->application = nullptr;
    }
}


/// ----------------------------------------------------------------------
/// \brief Procesa la initcialitzacio de l'aplicacio.
///
void Application::onInitialize() {

	// if (initializeEvent != nullptr)
	//     initializeEvent->execute(this);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la finalitzacio de l'aplicacio.
///
void Application::onTerminate() {

	// if (terminateEvent != nullptr)
	//     terminateEvent->execute(this);
}
