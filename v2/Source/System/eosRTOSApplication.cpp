module;


#include "eos.h"
#include "RTOS/rtosKernel.h"
#include "RTOS/rtosTask.h"
#include "System/Collections/eosIntrusiveForwardList.h"


export module Eos.System.Application.RTOS;


import Eos.Services.Service;
import Eos.System.Application;


export namespace eos {

    /// \brief Clase que representa l'aplicacio.
    ///
    class RTOSApplication: public Application {
        private:
            struct ServiceInfo;
            using ServiceInfoList = IntrusiveForwardList<ServiceInfo, 0>;
            using ServiceInfoListNode = IntrusiveForwardListNode<ServiceInfo, 0>;
            struct ServiceInfo: ServiceInfoListNode {
    			Service *service;
    		};

        protected:
            struct ApplicationParams {
            	uint32_t stackDepth;
            	rtos::Task::Priority priority;
            	const char *name;
            };

        private:
            static constexpr const char *_defaultName = "Application";
            static constexpr unsigned _defaultStackDepth = 256;
            static constexpr rtos::Task::Priority _defaultPriority = rtos::Task::Priority::normal;

        private:
            rtos::Task::Event<RTOSApplication> _taskEvent;
            rtos::Task *_task;
            bool _running;

            ServiceInfoList _serviceInfoList;

        private:
            RTOSApplication(const RTOSApplication&) = delete;
            RTOSApplication& operator=(const RTOSApplication&) = delete;

            void taskEventHandler(rtos::Task *task, rtos::Task::EventArgs *args);
            void onRun() override;

        protected:
            RTOSApplication();
            ~RTOSApplication();

            virtual void onExecute() = 0;
            virtual void onInitialize(ApplicationParams &params);

        public:
            void addService(Service *service);
            void removeService(Service *service);
            void removeServices();
    };
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::RTOSApplication::RTOSApplication() :
	_taskEvent (*this, &RTOSApplication::taskEventHandler),
	_task {nullptr},
	_running {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Descrutor.
///
eos::RTOSApplication::~RTOSApplication(){

	if (_task != nullptr)
		delete _task;
}


/// ----------------------------------------------------------------------
/// \brief    Callback de la tasca de l'aplicacio.
///
void eos::RTOSApplication::taskEventHandler(
	rtos::Task *task,
	rtos::Task::EventArgs *args) {

	onExecute();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres de l'aplicacio.
/// \param    params: Els parametres.
///
void eos::RTOSApplication::onInitialize(
	ApplicationParams &params) {

}


/// ----------------------------------------------------------------------
/// \brief    Posa l'aplicacio i els serveix en en execucio.
///
void eos::RTOSApplication::onRun() {

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
void eos::RTOSApplication::addService(
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
void eos::RTOSApplication::removeService(
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
void eos::RTOSApplication::removeServices() {

	//_serviceInfoList.clear();
}
