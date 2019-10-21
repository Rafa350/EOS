#ifndef __eosService__
#define	__eosService__


// EOS includes
//
#include "eos.h"
#include "System/Core/eosString.h"
#include "System/Core/eosTask.h"


namespace eos {

	struct ServiceConfiguration {
		const char *serviceName;
		int stackSize;
		TaskPriority priority;
	};
    
    class Application;

    class Service: private IRunable {
        private:
            Application *application;
            String name;
            Task thread;

        private :
            Service(const Service &service) = delete;
            Service& operator=(const Service&) = delete;

            void run(Task *thread);

        protected:
            inline Application *getApplication() const { return application; }
            inline Task *getThread() { return &thread; }
            virtual void onInitialize();
            virtual void onTask();
            virtual void onTick();

        public :
            Service(Application *application, const ServiceConfiguration &configuration);
            virtual ~Service();

            void initialize();
            void tick();
            void task();

            inline const String& getName() const { return name; }
            
        friend void link(Application *application, Service *service);
        friend void unlink(Application *application, Service *service);
    };
}


#endif	// __eosService__
