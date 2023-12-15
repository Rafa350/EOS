#pragma once
#ifndef __eosService__
#define __eosService__


// EOS includes
//
#include "eos.h"
#include "System/eosEvents.h"
#include "System/Core/eosTask.h"


namespace eos {

    class Service;

    struct ServiceEventArgs: public EventArgs<Service> {

    	inline ServiceEventArgs(Service *service):
    		EventArgs(service) {
    	}
    };

    /// \brief Clase que representa un servei.
    ///
    class Service {
    	public:
			enum class State {
				created,
				initialized,
				started,
				running,
				stopped,
				terminated
			};

    	private:
    		State _state;

        protected:
            Service();
            Service(const Service&) = delete;
            Service& operator=(const Service&) = delete;

            virtual void onInitialize();
            virtual void onTerminate();
            virtual void onTaskStart();
            virtual void onTask();

        public:
            virtual ~Service() = default;

            void initialize();
            void terminate();
            void taskStart();
            void taskRun();

            inline State getState() const {
            	return _state;
            }
    };

}


#endif // __eosService__
