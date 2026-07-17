#pragma once
#ifndef __eosFormsService__
#define __eosFormsService__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "Services/Forms/eosForm.h"
#include "System/Core/eosQueue.h"


namespace eos {

    class DisplayDriver;
    class Graphics;

    class FormsService: public Service {
        private:
    		constexpr static const char *_serviceName = "Forms";
    		constexpr static uint32_t _serviceStackDepth = 280;
    		constexpr static rtos::Task::Priority _servicePriority = rtos::Task::Priority::low;

        private:
    		using MessageQueue = Queue<FormMessage>;

        private:
            DisplayDriver * const _drvDisplay;
            VisualList  _forms;
            Form *_activeForm;
            MessageQueue _messageQueue;

        protected:
			void onExecute() override;
			void onInitialize(ServiceParams &params) override;

        public:
            FormsService(DisplayDriver *drvDisplay);

            void addForm(Form *form);

            void sendMessage(FormMessage &message);
            bool postMessage(FormMessage &message, Time blockTime);

            bool postInitializeMessage(Time blockTime);
            bool postKeyboardMessage(KeyboardMessageID id, Time blockTime);
            bool postSelectorMessage(SelectorMessageID id, Time blockTime);

            void setActiveForm(Form *form);
    };

}


#endif // __eosFormsService__
