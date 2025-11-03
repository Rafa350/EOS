#include "eos.h"
#include "eosAssert.h"
#include "Services/eosService.h"
#include "System/eosRTOSApplication.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosKernel.h"


using namespace eos;


constexpr const char *applicationName = "Application";
constexpr unsigned applicationStackSize = 256;
constexpr Task::Priority applicationPriority = Task::Priority::normal;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
RTOSApplication::RTOSApplication() :
	_running {false},
	_appTask {nullptr},
	_appTaskCallback (*this, &RTOSApplication::appTaskCallbackHandler) {
}


/// ----------------------------------------------------------------------
/// \brief    Callback de la tasca de l'aplicacio.
///
void RTOSApplication::appTaskCallbackHandler(
	const TaskCallbackArgs &args) {

	onExecute();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres de l'aplicacio.
/// \param    params: Els parametres.
///
void RTOSApplication::onInitialize(
	ApplicationParams &params) {

}


/// ----------------------------------------------------------------------
/// \brief    Posa l'aplicacio i els serveix en en execucio.
///
void RTOSApplication::onRun() {

	ApplicationParams params = {
		.stackSize = applicationStackSize,
		.priority = applicationPriority
	};

	onInitialize(params);

	_appTask = new Task(
		params.stackSize,
		params.priority,
		applicationName,
		&_appTaskCallback,
		nullptr);

    // Inicia els serveis que s'hagin afeigit abans del inici del
	// planificador.
    //
    for (auto si: _serviceInfoList)
    	si->service->start();

    // Inicia el planificador i totes les tasques
    //
    _running = true;
    Kernel::pInst->startScheduler(); // Ja no retorna mai mes
    _running = false;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un servei a l'aplicacio.
/// \param    service: EL servei.
///
void RTOSApplication::addService(
	Service *service) {

	eosAssert(service != nullptr);

	auto si = new ServiceInfo;
	eosAssert(si != nullptr);

	si->service = service;

	_serviceInfoList.pushFront(si);
	if (_running)
		service->start();
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un servei de l'aplicacio
/// \param    service: El servei a eliminar.
///
void RTOSApplication::removeService(
    Service *service) {

    eosAssert(service != nullptr);

    /*for (auto si: _serviceInfoList) {
    	if (si->service == service) {
        	_serviceInfoList.remove(si);
    		break;
    	}
    }*/
}


/// ----------------------------------------------------------------------
/// \brief    Elimina tots els serveis de l'aplicacio.
///
void RTOSApplication::removeServices() {

	//_serviceInfoList.clear();
}
