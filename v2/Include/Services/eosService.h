#pragma once


// EOS includes
//
#include "eos.h"
#include "RTOS/rtosTask.h"
#include "System/eosEvents.h"


namespace eos {

    /// \brief Clase que representa un servei.
    ///
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
            Service(const Service&) = delete;
            Service& operator=(const Service&) = delete;

            virtual void onStart();
            virtual void onStarted();
            virtual void onStop();
            virtual void onStopped();
            virtual void onExecute() = 0;
            virtual void onInitialize(ServiceParams &params);

            bool stopSignal() const;

        public:
            virtual ~Service();

            void start();
            void stop();

            inline State getState() const { return _state; }
    };

}
