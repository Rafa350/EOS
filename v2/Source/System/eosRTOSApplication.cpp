#include "eos.h"
#include "RTOS/rtosKernel.h"
#include "RTOS/rtosTask.h"
#include "Services/eosService.h"
#include "System/eosRTOSApplication.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
RTOSApplication::RTOSApplication() :
	_taskEvent (*this, &RTOSApplication::taskEventHandler),
	_task {nullptr},
	_running {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Descrutor.
///
RTOSApplication::~RTOSApplication(){

	if (_task != nullptr)
		delete _task;
}


/// ----------------------------------------------------------------------
/// \brief    Callback de la tasca de l'aplicacio.
///
void RTOSApplication::taskEventHandler(
	rtos::Task *task,
	rtos::TaskEventArgs *args) {

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
		.stackDepth = _defaultStackDepth,
		.priority = _defaultPriority,
		.name = _defaultName
	};

	onInitialize(params);

	_task = new rtos::Task(
		params.stackDepth,
		params.priority,
		params.name,
		_taskEvent);

    // Inicia els serveis que s'hagin afeigit abans del inici del
	// planificador.
    //
    for (auto si: _serviceInfoList)
    	si->service->start();

    // Inicia el planificador i totes les tasques
    //
    _running = true;
    rtos::Kernel::startScheduler(); // Ja no retorna mai mes

    _running = false;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un servei a l'aplicacio.
/// \param    service: EL servei.
///
void RTOSApplication::addService(
	Service *service) {

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
