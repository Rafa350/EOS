#pragma once


// EOS includes
//
#include "eos.h"
#include "System/eosApplicationBase.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosTimer.h"



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
            	unsigned stackSize;
            	Task::Priority priority;
            };

        private:
            ServiceInfoList _serviceInfoList;
            bool _running;
            Task *_appTask;
            TaskCallback<RTOSApplication> _appTaskCallback;

        private:
            RTOSApplication(const RTOSApplication&) = delete;
            RTOSApplication& operator=(const RTOSApplication&) = delete;

            void appTaskCallbackHandler(const TaskCallbackArgs &args);
            void onRun() override;

        protected:
            RTOSApplication();

            virtual void onExecute() = 0;
            virtual void onInitialize(ApplicationParams &params);

            inline Task* getTask() const {
            	return _appTask;
            }

        public:
            void addService(Service *service);
            void removeService(Service *service);
            void removeServices();
    };
}


