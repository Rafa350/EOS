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
		String serviceName;
		unsigned stackSize;
		TaskPriority priority;
	};

    class Service: private IRunable {
        private:
            static int idCount;
            int id;
            Application *pApplication;
            String name;
            Task thread;

        private :
            void run(Task *pThread);

        protected:
            inline Application *getApplication() const { return pApplication; }
            inline Task *getThread() { return &thread; }
            virtual void onInitialize();
            virtual void onTask();
            virtual void onTick();

        public :
            Service(Application *pApplication, const ServiceConfiguration &configuration);
            virtual ~Service();

            void initialize();
            void tick();
            void task();

            inline int getId() const { return id; }
            inline const String& getName() const { return name; }
            
        friend void Application::addService(Service *pService);
        friend void Application::removeService(Service *pService);

        Service(const Service &service) = delete;
        Service& operator=(const Service&) = delete;
    };
}


#endif	// __eosService__
