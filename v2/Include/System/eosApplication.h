#ifndef __eosApplication__
#define	__eosApplication__


// EOS includes
//
#include "eos.h"
#include "HAL/halTMR.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosDynamicArray.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosTimer.h"


namespace eos {

    class Application;
    class Service;

    void link(Application* application, Service* service);
    void unlink(Application* application, Service* service);
    
    /// \brief Clase que representa l'aplicacio.
    ///
    class Application {
        private:
            typedef DynamicArray<Service*> ServiceList;
            typedef DynamicArray<Service*>::Iterator ServiceListIterator;
            typedef DynamicArray<Task*> TaskList;
            typedef CallbackP1<Application, const Task::EventArgs&> TaskEventCallback;
#ifdef USE_APPLICATION_TICK            
            typedef CallbackP1<Application, const Timer::EventArgs&> TimerEventCallback;
#endif            

            bool initialized;
            ServiceList services;
            TaskList tasks;
            TaskEventCallback taskEventCallback;
#ifdef USE_APPLICATION_TICK            
            TimerEventCallback timerEventCallback;
            Timer timer;
#endif            

            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;

            void initializeServices();
            void terminateServices();
            void runServices();
            void taskEventHandler(const Task::EventArgs& args);
#ifdef USE_APPLICATION_TICK            
            void timerEventHandler(const Timer::EventArgs& args);
#endif

        protected:
            virtual void onInitialize();
            virtual void onTerminate();
#ifdef USE_APPLICATRION_TICK            
            virtual void onTick();
#endif

        public:
            Application();
            virtual ~Application();

            void run();
#ifdef USE_APPLICATION_TICK            
            void tick();
#endif

            void addService(Service* service);
            void removeService(Service* service);
            void removeServices();

            inline bool isInitialized() const { return initialized; }

        friend void link(Application* application, Service* service);
        friend void unlink(Application* application, Service* service);
    };

}


#endif // __eosApplication__


