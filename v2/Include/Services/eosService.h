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
            void run(Task *pTask);

        protected:
            inline Task *getTask() { return &task; }
            virtual void onSetup();
            virtual void onLoop();
            virtual void onTick();

        public :
            Service(const ServiceInitializeInfo *pInit);
            Service(Application *pApplication, const char *name, unsigned stackSize, TaskPriority priority);
            virtual ~Service();

            inline const char *getName() const { return name; }
            inline Application *getApplication() const { return pApplication; }

        friend Application;
    };
}


#endif	// __eosService__
