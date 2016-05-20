#ifndef __EOS_SERVICES_FORMS_FORMS_HPP
#define __EOS_SERVICES_FORMS_FORMS_HPP


#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "System/Collections/eosList.hpp"
#include "System/Collections/eosQueue.hpp"
#ifdef eosFormsService_UseSelector
#include "Services/Forms/eosSelector.hpp"
#endif
#ifdef eosFormsService_UseKeyboard
#include "Services/Forms/eosKeyboard.hpp"
#endif


#define MSG_NULL               0

#ifdef eosFormsService_UseSelector
#define MSG_SELECTOR         100       // Event del selector
#define EV_SELECTOR_INC        1       // -Increment del selector
#define EV_SELECTOR_DEC        2       // -Decrement del selector
#define EV_SELECTOR_CLICK      3       // -Click del boto
#endif

#ifdef eosFormsService_UseKeyboard
#define MSG_KEYBOARD         101       // Event del teclat
#define EV_KEYBOARD_UP         1       // -Tecla UP
#define EV_KEYBOARD_DOWN       2       // -Tecla DOWN
#define EV_KEYBOARD_LEFT       3       // -Tecla LEFT
#define EV_KEYBOARD_RIGHT      4       // -Tecla RIGHT
#define EV_KEYBOARD_OK         5       // -Tecla OK
#endif

#ifdef eosFormsService_UseTouchpad
#define MSG_TOUCHPAD         102       // Event del panell tactil
#endif

#define MSG_COMMAND          110       // Comanda
#define MSG_NOTIFY           111       // Event de nofificacio d'un altre form


namespace eos {
    
    class Form;
    typedef Form *FormHandle;
    
    class FormsDisplay;
    typedef FormsDisplay *FormsDisplayHandle;
    
    class FormsService;
    typedef FormsService *FormsServiceHandle;
    
    class Display;
    
    enum class SelectorDirection {
        forward,
        backward
    };
    
    struct MsgSelector {
        unsigned event;
        int position;
        unsigned state;
    };

#ifdef eosFormsService_UseKeyboard    
    struct MsgKeyboard {
        unsigned event;
        unsigned keyCode;
    };
#endif    
    
#ifdef eosFormsService_UseTouchpad    
    struct MsgTouchpad {
        unsigned event;
    };
#endif    

    struct Message {
        unsigned id;
        FormHandle target;
        union {
#ifdef eosFormsService_UseSelector            
            MsgSelector msgSelector;
#endif            
#ifdef eosFormsService_UseKeyboard            
            MsgKeyboard msgKeyboard;
#endif            
#ifdef eosFormsService_UseTouchpad            
            MsgTouchpad msgTouchpad;
#endif
        };
    };
    
    typedef Queue<Message> MessageQueue;
    
    class FormsService: private IRunable {
        private:
            typedef List<FormHandle> FormList;
            typedef ListIterator<FormHandle> FormListIterator;
            
        private:
            Task task;
            MessageQueue *messageQueue;
            FormsDisplayHandle display;
            FormList forms;
            FormList destroyForms;
            FormHandle activeForm;     
            
        public:
            FormsService(MessageQueue *messageQueue, FormsDisplayHandle display);
            virtual ~FormsService();
            void add(FormHandle form);
            void remove(FormHandle form);
            void destroy(FormHandle form);
            FormHandle activate(FormHandle form);
            FormHandle getActiveForm() const { return activeForm; }
        private:
            void run();
            
        friend class Form;
    };
    
    class FormsDisplay {
        private:
            Display *display;
            
        public:
            FormsDisplay(Display *display);
            void beginDraw();
            void endDraw();
            void clear();
            void setColor(unsigned color);
            void drawLine(int x1, int y1, int x2, int y2);
            void drawRectangle(int x, int y, int width, int height);
            void drawText(int x, int y, const char *text, unsigned offset, unsigned length);
            void fillRectangle(int x, int y, int width, int height);
    };
       
    class Form {
        private:
            typedef ICallbackP1<FormHandle> ISelectorPressEvent;
        private:
            FormsServiceHandle service;
            FormHandle parent;
            bool paintPending;
#ifdef eosFormsService_UseSelector            
            ISelectorPressEvent *evSelectorPress;
#endif
            //int x;
            //int y;
            //int width;
            //int height;
            
        public:
            Form(FormsServiceHandle service, FormHandle parent);
            void destroy() { service->destroy(this); }
            void refresh();
            void activate() { service->activate(this); }
            FormHandle getParent() const { return parent; }
            FormsServiceHandle getService() const { return service; }

#ifdef eosFormsService_UseSelector            
            template <class cls>
            void setSelectorPressEvent(cls *instance, void (cls::*method)(FormHandle)) { 
                
                evSelectorPress = new CallbackP1<cls, FormHandle>(instance, method);
            }
#endif            
            
        protected:
            virtual ~Form();
            virtual void dispatchMessage(Message &message);
            virtual void onActivate(FormHandle deactivateForm); 
            virtual void onDeactivate(FormHandle activateForm) {}
            virtual void onPaint(FormsDisplayHandle display) {}
#ifdef eosFormsService_UseSelector            
            virtual void onSelectorMove(int position, SelectorDirection direction);
            virtual void onSelectorPress();
            virtual void onSelectorRelease();
#endif
#ifdef eosFormsService_UseKeyboard
            virtual void onKeyPress(unsigned key);
            virtual void onKeyRelease(unsigned key);
#endif            
            
        friend class FormsService;
    };
}


#endif