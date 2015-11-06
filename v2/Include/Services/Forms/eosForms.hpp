#ifndef __EOS_FORMS_HPP
#define __EOS_FORMS_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosList.hpp"
#include "System/eosQueue.hpp"
#include "Services/Forms/eosDisplay.hpp"


#define MSG_NULL               0

#define MSG_SELECTOR         100       // Event del selector
#define EV_SELECTOR_INC        1       // -Increment del selector
#define EV_SELECTOR_DEC        2       // -Decrement del selector
#define EV_SELECTOR_CLICK      3       // -Click del boto

#define MSG_KEYBOARD         101       // Event del teclat
#define EV_KEYBOARD_UP         1       // -Tecla UP
#define EV_KEYBOARD_DOWN       2       // -Tecla DOWN
#define EV_KEYBOARD_LEFT       3       // -Tecla LEFT
#define EV_KEYBOARD_RIGHT      4       // -Tecla RIGHT
#define EV_KEYBOARD_OK         5       // -Tecla OK

#define MSG_COMMAND          102       // Comanda
#define MSG_NOTIFY           103       // Event de nofificacio d'un altre form


namespace eos {
    
    class Form;
    typedef Form *FormHandle;
    
    class FormsService;
    typedef FormsService *FormsServiceHandle;
    
    struct MsgSelector {
        unsigned event;
        int position;
        uint8_t state;
    };

    struct MsgKeyboard {
        unsigned event;
    };

    struct Message {
        unsigned id;
        FormHandle target;
        union {
            MsgSelector msgSelector;
            MsgKeyboard msgKeyboard;
        };
    };
    
    class MessageQueue {
        private:
            Queue<Message> queue;

        public: 
            MessageQueue();
            void send(Message &message, unsigned blockTime);
            bool receive(Message &message, unsigned blockTime);
    };
    
    class FormsService: public IRunable {
        private:
            typedef List<FormHandle> FormList;
            typedef ListIterator<FormHandle> FormListIterator;
            
        private:
            Task task;
            MessageQueue *messageQueue;
            DisplayServiceHandle displayService;
            FormList forms;
            FormHandle activeForm;            
            
        public:
            FormsService(MessageQueue *messageQueue, DisplayServiceHandle displayService);
            ~FormsService();
            void add(FormHandle form);
            FormHandle activate(FormHandle form);
            FormHandle getActiveForm() { return activeForm; }
        private:
            void run();
    };
       
    class Form {
        private:
            FormsServiceHandle service;
            FormHandle parent;
            bool paintPending;
            
        public:
            Form(FormsServiceHandle service, FormHandle parent);
            virtual ~Form();
            void refresh();
            void activate() { service->activate(this); }
            FormHandle getParent() { return parent; }
        protected:
            virtual void dispatchMessage(Message &message);
            virtual void onActivate(FormHandle deactivateForm) {} 
            virtual void onDeactivate(FormHandle activateForm) {}
            virtual void onPaint(DisplayServiceHandle displayService);
            
        friend class FormsService;
    };
}


#endif