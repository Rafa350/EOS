#ifndef __eosService__
#define	__eosService__

#include "eos.h"
#include "System/eosString.h"
#include "System/Core/eosTask.h"


namespace eos {

    class Application;

    /// \brief Clase que representa un servei.
    ///
    class Service: public IRunable {
        private:
    		bool initialized;
            Application *application;
            Task::Priority priority;

            Service(const Service &service) = delete;
            Service& operator=(const Service&) = delete;
            
        protected:
            inline Application *getApplication() const { return application; }
            virtual void onInitialize();
            virtual void onTask();
            virtual void onTick();
            
        public :
            Service(Application *application);
            virtual ~Service();

            void initialize();
            void tick();
            void task();
            void run(Task *thread);
            
            inline bool isInitialized() const { return initialized; }

            inline void setPriority(Task::Priority proprity) { this->priority = priority; }

            inline Task::Priority getPriority() const { return priority; }

        friend void link(Application *application, Service *service);
        friend void unlink(Application *application, Service *service);
    };
}


#endif	// __eosService__
