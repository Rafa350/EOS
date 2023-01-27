#pragma once
#ifndef __eosApplication__
#define	__eosApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosSingleLinkedList.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosTimer.h"


namespace eos {

    class Application;
    class Service;

    /// \brief Clase que representa l'aplicacio.
    ///
    class Application {
        private:
    		struct ServiceInfo {
    			Service *service;
    			Task::Priority priority;
    			unsigned stackSize;
    			const char *name;
    			Task *task;
    		};
    		typedef SingleLinkedList<ServiceInfo*> ServiceInfoList;
            typedef CallbackP1<Application, const Task::EventArgs&> TaskEventCallback;
#if Eos_ApplicationTickEnabled
            typedef CallbackP1<Application, const Timer::EventArgs&> TimerEventCallback;
#endif
        private:
            bool _initialized;
            ServiceInfoList _serviceInfoList;
            TaskEventCallback _taskEventCallback;
#if Eos_ApplicationTickEnabled
            TimerEventCallback _timerEventCallback;
            Timer timer;
#endif

            Application(const Application&) = delete;
            Application& operator=(const Application&) = delete;

            void initializeServices();
            void terminateServices();
            void runServices();
            void taskEventHandler(const Task::EventArgs &args);
#if Eos_ApplicationTickEnabled
            void timerEventHandler(const Timer::EventArgs &args);
#endif

        protected:
            Application();

            virtual void onInitialize();
            virtual void onTerminate();
#if Eos_ApplicationTickEnabled
            virtual void onTick();
#endif

        public:
            virtual ~Application();

            void run();
#if Eos_ApplicationTickEnabled
            void tick();
            void tmrInterruptFunction();
            static void tmrInterruptFunction(TMRHandler handler, void  params);
#endif

            void addService(Service *service, Task::Priority priority, unsigned stackSize, const char *name = nullptr);
            void removeService(Service *service);
            void removeServices();

            inline bool isInitialized() const { return _initialized; }
    };
}


#endif // __eosApplication__


