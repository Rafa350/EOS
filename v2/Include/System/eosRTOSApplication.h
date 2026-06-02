#pragma once
#ifndef __eosRTOSApplication__
#define __eosRTOSApplication__


// EOS includes
//
#include "eos.h"
#include "RTOS/rtosTask.h"
#include "System/eosApplicationBase.h"
#include "System/Collections/eosIntrusiveForwardList.h"


namespace eos {

    class Service;

    /// \brief Clase que representa l'aplicacio.
    ///
    class RTOSApplication: public ApplicationBase {
        private:
            struct ServiceInfo;
            using ServiceInfoList = IntrusiveForwardList<ServiceInfo, 0>;
            using ServiceInfoListNode = IntrusiveForwardListNode<ServiceInfo, 0>;
            struct ServiceInfo: ServiceInfoListNode {
    			Service *service;
    		};

        protected:
            struct ApplicationParams {
            	uint32_t stackDepth;
            	rtos::Task::Priority priority;
            	const char *name;
            };

        private:
            static constexpr const char *_defaultName = "Application";
            static constexpr unsigned _defaultStackDepth = 256;
            static constexpr rtos::Task::Priority _defaultPriority = rtos::Task::Priority::normal;

        private:
            rtos::Task::Event<RTOSApplication> _taskEvent;
            rtos::Task *_task;
            bool _running;

            ServiceInfoList _serviceInfoList;

        private:
            RTOSApplication(const RTOSApplication&) = delete;
            RTOSApplication& operator=(const RTOSApplication&) = delete;

            void taskEventHandler(rtos::Task *task, rtos::Task::EventArgs *args);
            void onRun() override;

        protected:
            RTOSApplication();
            ~RTOSApplication();

            virtual void onExecute() = 0;
            virtual void onInitialize(ApplicationParams &params);

        public:
            void addService(Service *service);
            void removeService(Service *service);
            void removeServices();
    };
}


#endif // __eosRTOSApplication__
