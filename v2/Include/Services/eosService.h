#ifndef __eosService__
#define	__eosService__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"


namespace eos {

	typedef struct {
		Application *application;
		const char *name;
		unsigned stackSize;
		TaskPriority priority;
	} ServiceInitializeInfo;

    class Service: private IRunable {
        private:
            Application *application;
            const char *name;
            Task task;
            
        private :
            void run(Task *task);
            
        protected:
            virtual void onSetup();
            virtual void onLoop();

        public :
            Service(const ServiceInitializeInfo *init);
            Service(Application *application, const char *name, unsigned stackSize, TaskPriority priority);
            virtual ~Service();

            inline const char *getName() const { return name; }
            inline Application *getApplication() const { return application; }

        friend void Application::addService(Service *service);
        friend void Application::removeService(Service *service);
    };
}


#endif	// __eosService__
