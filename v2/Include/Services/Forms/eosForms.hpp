#ifndef __EOS_FORMS_HPP
#define __EOS_FORMS_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "System/eosList.hpp"
#include "System/eosQueue.hpp"
#include "System/eosCallbacks.hpp"


#define EV_Form_onActivate(cls, instance, method) \
    new eos::CallbackP1<cls, eos::Form*>(instance, method)
#define EV_Form_onDeactivate(cls, instance, method) \
    new eos::CallbackP1<cls, eos::Form*>(instance, method)


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


typedef struct {
    unsigned command;
} MsgCommand;

typedef struct {
//    eosFormHandle hSender;
    unsigned event;
    void *params;
} MsgNotify;

typedef struct {
    unsigned event;
    int position;
    uint8_t state;
} MsgSelector;

typedef struct {
//    eosFormHandle hForm;
    unsigned id;
    union {
        MsgCommand msgCommand;
        MsgNotify msgNotify;
        MsgSelector msgSelector;
    };
} eosFormsMessage;


namespace eos {
    
    class Form;

    typedef List<Form*> FormList;
    typedef ListIterator<Form*> FormListIterator;
    
    typedef ICallbackP1<Form*> IFormEvent;
    
    
    class FormsService: public IRunable {
        private:
            typedef unsigned Message;
            typedef Queue<Message> MessageQueue;
            
        private:
            Task task;
            MessageQueue messageQueue;
            FormList forms;
            Form *activeForm;            
            
        public:
            FormsService();
            ~FormsService();
            void add(Form *form);
            Form *activate(Form *form);
            Form *getActiveForm() { return activeForm; }
            void sendMessage(Message message);
        private:
            void run();
    };
    
    class Form {
        private:
            FormsService *service;
            Form *parent;
            bool paintPending;
            IFormEvent *onActivate;
            IFormEvent *onDeactivate;
            
        public:
            Form(FormsService *service, Form *parent);
            void refresh();
            void paint();
            void activate();
            Form *getParent() { return parent; }
            inline void setOnActivate(IFormEvent *event) { onActivate = event; }
            inline void setOnDeactivate(IFormEvent *event) { onDeactivate = event; }
            
        friend class FormsService;
    };
}


#endif