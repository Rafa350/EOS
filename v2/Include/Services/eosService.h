#ifndef __eosService__
#define	__eosService__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"


namespace eos {

	struct ServiceInitInfo {
		Application *application;
		const char *name;
		unsigned stackSize;
		TaskPriority priority;
	};

    class Service: private IRunable {
        private:
            static int idCount;
            int id;
            Application *application;
            const char *name;
            Task thread;

        private :
            Service(const Service &service) = delete;
            Service& operator=(const Service&) = delete;
            
            void run(Task *pThread);

        protected:
            inline Application *getApplication() const { return application; }
            inline Task *getThread() { return &thread; }
            virtual void onInitialize();
            virtual void onTask();
            virtual void onTick();

        public :
            Service(const ServiceInitInfo *init);
            Service(Application *application, const char *name, unsigned stackSize, TaskPriority priority);
            virtual ~Service();

            void initialize();
            void tick();
            void task();

            inline int getId() const { return id; }
            
        friend void Application::addService(Service *service);
        friend void Application::removeService(Service *service);
    };
}


#endif	// __eosService__
