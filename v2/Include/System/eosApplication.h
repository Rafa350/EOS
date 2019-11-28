#ifndef __eosApplication__
#define	__eosApplication__

#include "eos.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosArrayList.h"
#include "System/Core/eosTask.h"


namespace eos {

	class Service;
    class String;

    void link(Application *application, Service *service);
    void unlink(Application *application, Service *service);

    /// \brief Clase que representa l'aplicacio.
    ///
    class Application {
    	private:
        	typedef ArrayList<Service*> ServiceList;
            typedef ArrayList<Task*> TaskList;
			typedef CallbackP1<Application, const Task::EventArgs&> TaskEventCallback;

            bool initialized;
            ServiceList services;
            TaskList tasks;
            TaskEventCallback taskEventCallback;

            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;

            void initializeServices();
            void runServices();
            void taskEventHandler(const Task::EventArgs &args);

        protected:
            virtual void onInitialize();
            virtual void onTerminate();
            virtual void onTick();

        public:
            Application();
            virtual ~Application();

            void run();
            void tick();

            void addService(Service *service);
            void removeService(Service *service);
            void removeServices();

            inline bool isInitialized() const { return initialized; }

        friend void link(Application *application, Service *service);
        friend void unlink(Application *application, Service *service);
    };
}


#endif // __eosApplication__


