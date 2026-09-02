module;


#include "eos.h"
#include "RTOS/rtosTask.h"


export module Eos.Services.Service;


import Eos.System.Application;


export namespace eos {

    class Service {
    	public:
			enum class State {
				stop,
				run
			};

    	protected:
			struct ServiceParams {
				const char *name;
				rtos::Task::Priority priority;
				uint32_t stackDepth;
			};

    	private:
			static constexpr const char *_defaultName = "Service";
			static constexpr unsigned _defaultStackDepth = 256;
			static constexpr rtos::Task::Priority _defaultPriority = rtos::Task::Priority::normal;

    	private:
    		rtos::Task::Event<Service> _taskEvent;
    		rtos::Task *_task;
    		State _state;
    		volatile bool _stopSignal;

    	private:
    		void taskEventHandler(rtos::Task *task, rtos::Task::EventArgs *args);

        protected:
            Service();
			
            virtual void onStart();
            virtual void onStarted();
            virtual void onStop();
            virtual void onStopped();
            virtual void onExecute() = 0;
            virtual void onInitialize(ServiceParams &params);

            bool stopSignal() const;

        public:
            Service(const Service&) = delete;
            Service(const Service&&) = delete;
            virtual ~Service();

            void start();
            void stop();

            rtos::Task * getTask() const { return _task; }
            State getState() const { return _state; }

			Service& operator=(const Service&) = delete;
            Service& operator=(const Service&&) = delete;
    };

}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::Service::Service():
	_taskEvent {*this, &Service::taskEventHandler},
	_task {nullptr},
	_state {State::stop},
	_stopSignal {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Destructor.
///
eos::Service::~Service() {

	if (_task != nullptr)
		delete _task;
}


/// ----------------------------------------------------------------------
/// \brief    Inicia l'execucio del servei.
///
void eos::Service::start() {

	if (_state == State::stop) {

		ServiceParams params = {
			.name = _defaultName,
			.priority = _defaultPriority,
			.stackDepth = _defaultStackDepth
		};

		onInitialize(params);

		onStart();
		_task = new rtos::Task(
			params.stackDepth,
			params.priority,
			params.name,
			_taskEvent);

		_state = State::run; //******** Aqui?
	}
}


/// ----------------------------------------------------------------------
/// \brief    Atura l'execucio del servei.
///
void eos::Service::stop() {

	if (_state == State::run) {
		onStop();
		_stopSignal = true;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si cal aturar el servei.
/// \return   True en cas afirmatiu.
///
bool eos::Service::stopSignal() const {

	return _stopSignal;
}


/// ----------------------------------------------------------------------
/// \brief    Handler de la tasca.
/// \params   args: Parametres.
///
void eos::Service::taskEventHandler(
	rtos::Task *task,
	rtos::Task::EventArgs *args) {

	_state = State::run; //********* O aqui?
	onStarted();
	onExecute();
	_state = State::stop;
	onStopped();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els parametres del servei.
/// \param    params: Els parametres del servei.
///
void eos::Service::onInitialize(
	ServiceParams &paramms) {

}


/// ----------------------------------------------------------------------
/// \brief    Proces al inici del servei.
///
void eos::Service::onStart() {

}


/// ----------------------------------------------------------------------
/// \brief    Proces un cop iniciat el servei.
///
void eos::Service::onStarted() {

}


/// ----------------------------------------------------------------------
/// \brief    Proces al aturar el servei.
///
void eos::Service::onStop() {

}


/// ----------------------------------------------------------------------
/// \brief    Proces un cop aturar el servei.
///
void eos::Service::onStopped() {

}
