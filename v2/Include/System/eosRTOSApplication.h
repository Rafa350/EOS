#pragma once
#ifndef __eosRTOSApplication__
#define	__eosRTOSApplication__


// EOS includes
//
#include "eos.h"
#include "System/eosApplicationBase.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosList.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosTimer.h"


namespace eos {

    class Service;

    /// \brief Clase que representa l'aplicacio.
    ///
    class RTOSApplication: public ApplicationBase {
        private:
    		struct ServiceInfo {
    			Service *service;
    			Task::Priority priority;
    			unsigned stackSize;
    			const char *name;
    			Task *task;
    		};
    		typedef List<ServiceInfo*> ServiceInfoList;
            typedef CallbackP1<RTOSApplication, const Task::EventArgs&> TaskEventCallback;
#if Eos_ApplicationTickEnabled
            typedef CallbackP1<RTOSApplication, const Timer::EventArgs&> TimerEventCallback;
#endif
        private:
            ServiceInfoList _serviceInfoList;
            TaskEventCallback _taskEventCallback;
#if Eos_ApplicationTickEnabled
            TimerEventCallback _timerEventCallback;
            Timer timer;
#endif

            RTOSApplication(const RTOSApplication&) = delete;
            RTOSApplication& operator=(const RTOSApplication&) = delete;

            void initializeServices() override;
            void terminateServices() override;
            void runServices() override;
            void taskEventHandler(const Task::EventArgs &args);
#if Eos_ApplicationTickEnabled
            void timerEventHandler(const Timer::EventArgs &args);
#endif

        protected:
            RTOSApplication();

        public:
            void addService(Service *service, Task::Priority priority, unsigned stackSize, const char *name = nullptr);
            void removeService(Service *service);
            void removeServices();
    };
}


#endif // __eosRTOSApplication__

