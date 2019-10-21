#ifndef __eosService__
#define	__eosService__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"
#include "System/Core/eosString.h"
#include "System/Core/eosTask.h"


namespace eos {

	struct ServiceConfiguration {
		const char *serviceName;
		int stackSize;
		TaskPriority priority;
	};
    
    typedef unsigned ServiceId;

    class Service: private IRunable {
        private:
            static ServiceId idCount;
            ServiceId id;
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

            inline ServiceId getId() const { return id; }
            inline const String& getName() const { return name; }
            
        friend void Application::addService(Service *service);
        friend void Application::removeService(Service *service);
    };
}


#endif	// __eosService__
