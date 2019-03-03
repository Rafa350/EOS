#ifndef __eosService__
#define	__eosService__


// EOS includes
//
#include "eos.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"


namespace eos {

	typedef struct {
		Application *pApplication;
		const char *name;
		unsigned stackSize;
		TaskPriority priority;
	} ServiceInitializeInfo;

    class Service: private IRunable {
        private:
            Application *pApplication;
            const char *name;
            Task task;

        private :
            Service(const Service &service) = delete;
            Service& operator=(const Service&) = delete;
            void run(Task *pTask);

        protected:
            inline Application *getApplication() const { return pApplication; }
            inline Task *getTask() { return &task; }
            virtual void onInitialize();
            virtual void onTask();
            virtual void onTick();

        public :
            Service(const ServiceInitializeInfo *pInit);
            Service(Application *pApplication, const char *name, unsigned stackSize, TaskPriority priority);
            virtual ~Service();

            void initialize();
            void tick();

            inline const char *getName() const { return name; }

        friend void Application::addService(Service *pService);
        friend void Application::removeService(Service *pService);
    };
}


#endif	// __eosService__
