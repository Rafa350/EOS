#ifndef __EOS_FORMS_HPP
#define __EOS_FORMS_HPP


#ifndef __EOS_HPP
#include "eos.hpp"
#endif

#ifndef __EOS_TASK_HPP
#include "System/Core/eosTask.hpp"
#endif

#ifndef __EOS_LIST_HPP
#include "System/Collections/eosList.hpp"
#endif

#ifndef __EOS_QUEUE_HPP
#include "System/Collections/eosQueue.hpp"
#endif

#ifndef __EOS_DISPLAY_HPP
#include "Controllers/eosDisplay.hpp"
#endif


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

#define MSG_TOUCHPAD         102

#define MSG_COMMAND          110       // Comanda
#define MSG_NOTIFY           111       // Event de nofificacio d'un altre form


namespace eos {
    
    class Form;
    typedef Form *FormHandle;
    
    class FormsDisplay;
    typedef FormsDisplay *FormsDisplayHandle;
    
    class FormsService;
    typedef FormsService *FormsServiceHandle;
    
    enum class SelectorDirection {
        forward,
        backward
    };
    
    struct MsgSelector {
        unsigned event;
        int position;
        uint8_t state;
    };

    struct MsgKeyboard {
        unsigned event;
        unsigned keyCode;
    };
    
    struct MsgTouchpad {
        unsigned event;
    };

    struct Message {
        unsigned id;
        FormHandle target;
        union {
            MsgSelector msgSelector;
            MsgKeyboard msgKeyboard;
            MsgTouchpad msgTouchpad;
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
            FormsService(MessageQueue *messageQueue, DisplayControllerHandle displayController);
            ~FormsService();
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
            //int x;
            //int y;
            //int width;
            //int height;
            DisplayControllerHandle displayController;
            
        public:
            FormsDisplay(DisplayControllerHandle displayController);
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
            ISelectorPressEvent *evSelectorPress;
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

            template <class cls>
            void setSelectorPressEvent(cls *instance, void (cls::*method)(FormHandle)) { 
                
                evSelectorPress = new CallbackP1<cls, FormHandle>(instance, method);
            }
            
        protected:
            virtual ~Form();
            virtual void dispatchMessage(Message &message);
            virtual void onActivate(FormHandle deactivateForm) {} 
            virtual void onDeactivate(FormHandle activateForm) {}
            virtual void onPaint(FormsDisplayHandle display) {}
            virtual void onSelectorMove(int position, SelectorDirection direction);
            virtual void onSelectorPress();
            virtual void onSelectorRelease();
            virtual void onKeyPress(unsigned keyCode);
            virtual void onKeyRelease(unsigned keyCode);
            
        friend class FormsService;
    };
}


#endif