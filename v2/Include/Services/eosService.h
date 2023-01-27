#ifndef __eosService__
#define	__eosService__


// EOS includes
//
#include "eos.h"
#include "SYstem/eosEvents.h"
#include "System/eosString.h"
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
				ready,
				running,
				finished
			};

    	private:
    		State _state;

        protected:
            Service();
            Service(const Service&) = delete;
            Service& operator=(const Service&) = delete;

            virtual void onInitialize();
            virtual void onTerminate();
            virtual void onTask();
#if Eos_ApplicationTickEnabled
            virtual void onTick();
#endif

        public:
            virtual ~Service() = default;

            void initialize();
            void terminate();
#if Eos_ApplicationTickEnabled
            void tick();
#endif
            void task();

            inline State getState() const {
            	return _state;
            }
    };

}


#endif	// __eosService__
