#pragma once
#ifndef __eosService__
#define __eosService__


// EOS includes
//
#include "eos.h"
#include "System/eosEvents.h"
#include "System/Core/eosTask.h"


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
				Task::Priority priority;
				unsigned stackSize;
			};

    	private:
    		State _state;
    		Task * _task;
    		TaskCallback<Service> _taskCallback;
    		bool _stopSignal;

    	private:
    		void taskCallbackHandler(const TaskCallbackArgs &args);

        protected:
            Service();
            Service(const Service&) = delete;
            Service& operator=(const Service&) = delete;

            virtual void onStart();
            virtual void onStarted();
            virtual void onStop();
            virtual void onStopped();
            virtual void onExecute() = 0;
            virtual void initService(ServiceParams &params);

            bool stopSignal() const;

        public:
            virtual ~Service() = default;

            void start();
            void stop();

            inline State getState() const {
            	return _state;
            }
    };

}


#endif // __eosService__
