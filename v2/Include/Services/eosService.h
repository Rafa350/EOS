#ifndef __EOS_SERVICE_H
#define	__EOS_SERVICE_H


#include "eos.h"
#include "System/eosApplication.h"
#include "System/Core/eosTask.h"


namespace eos {
       
    class Service: private IRunable {
        private:
            Application *application;
            const char *name;
            Task task;
        
        public :
            Service(Application *application, const char *name, unsigned stackSize, TaskPriority priority);
            virtual ~Service();
            
            inline const char *getName() const { return name; }   
            inline Application *getApplication() const { return application; }

        friend void Application::addService(Service *service);
        friend void Application::removeService(Service *service);
    };
}


#endif	
