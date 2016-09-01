#ifndef __EOS_SERVICES_FORMS_FORMS_HPP
#define __EOS_SERVICES_FORMS_FORMS_HPP


#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "System/Collections/eosList.hpp"
#include "System/Core/eosQueue.hpp"
#include "Controllers/Display/eosDisplay.hpp"
#ifdef eosFormsService_UseSelector
#include "Services/eosSelector.hpp"
#endif
#ifdef eosFormsService_UseKeyboard
#include "Services/eosKeyboard.hpp"
#endif


#define MSG_NULL               0       // Event NULL
#define MSG_PAINT              1       // Repintat del form

#ifdef eosFormsService_UseSelector
#define MSG_SELECTOR         100       // Event del selector
#endif

#ifdef eosFormsService_UseKeyboard
#define MSG_KEYBOARD         101       // Event del teclat
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
    
    struct MsgPaint {
        FormsDisplayHandle display;
    };
    
#ifdef eosFormsService_UseSelector
    
    typedef enum class {
        inc,
        dec,
        press,
        release
    } SelectorEvent;
    
    typedef enum class {
        forward,
        backward
    } SelectorDirection;
    
    struct MsgSelector {
        SelectorEvent event;
        SelectorPosition position;
        SelectorState state;
    };
#endif    

#ifdef eosFormsService_UseKeyboard    
    
    typedef enum class {
        up,
        down,
        left,
        right,
        enter
    } KeyCode;
    
    typedef enum class {
        press,
        release
    } KeyboardEvent;
    
    struct MsgKeyboard {
        KeyboardEvent event;
        KeyCode keyCode;
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
            MsgPaint msgPaint;
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
    typedef MessageQueue *MessageQueueHandle;
    
    class FormsService: private IRunable {
        private:
            typedef List<FormHandle> FormList;
            typedef ListIterator<FormHandle> FormListIterator;
            
        private:
            Task task;
            MessageQueueHandle messageQueue;
            FormsDisplayHandle display;
            FormList forms;
            FormList destroyForms;
            FormHandle activeForm;     
            
        public:
            FormsService(MessageQueueHandle messageQueue, FormsDisplayHandle display);
            virtual ~FormsService();
            void add(FormHandle form);
            void remove(FormHandle form);
            void destroy(FormHandle form);
            void refresh(FormHandle form);
            void refresh(FormHandle form, int16_t x, int16_t y, int16_t width, int16_t height);
            FormHandle activate(FormHandle form);
            inline FormHandle getActiveForm() const { return activeForm; }
        private:
            void run();
            
        friend class Form;
    };
    
    class FormsDisplay {
        private:
            Display *display;
            
        public:
            FormsDisplay(Display *display);
            Display* getDisplay() const { return display; }
            void beginDraw();
            void endDraw();
            void clear(Color color);
            void setColor(Color color);
            void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void drawRectangle(int16_t x, int16_t y, int16_t width, int16_t height);
            void drawText(int16_t x, int16_t y, const char *text, int16_t offset, int16_t length);
            void fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height);
    };
       
    class Form {
        private:
            typedef ICallbackP1<FormHandle> ISelectorPressEvent;
            typedef ICallbackP1<FormHandle> ISelectorReleaseEvent;
        private:
            FormsServiceHandle service;
            FormHandle parent;
#ifdef eosFormsService_UseSelector            
            ISelectorPressEvent *evSelectorPress;
            ISelectorReleaseEvent *evSelectorRelease;
#endif
            int16_t x;
            int16_t y;
            int16_t width;
            int16_t height;
            
        public:
            Form(FormsServiceHandle service, FormHandle parent);
            void destroy() { service->destroy(this); }
            void refresh() { service->refresh(this); }
            void refresh(int16_t x, int16_t y, int16_t width, int16_t height) { service->refresh(this, x, y, width, height); }
            void activate() { service->activate(this); }
            inline FormHandle getParent() const { return parent; }
            inline FormsServiceHandle getService() const { return service; }
            inline int16_t getX() const { return x; }
            inline int16_t getY() const { return y; }

#ifdef eosFormsService_UseSelector            
            template <class cls>
            void setSelectorPressEvent(cls *instance, void (cls::*method)(FormHandle)) { 
                
                evSelectorPress = new CallbackP1<cls, FormHandle>(instance, method);
            }
            
            template <class cls>
            void setSelectorReleaseEvent(cls *instance, void (cls::*method)(FormHandle)) { 
                
                evSelectorRelease = new CallbackP1<cls, FormHandle>(instance, method);
            }
#endif            
            
        protected:
            virtual ~Form();
            virtual void dispatchMessage(Message &message);
            virtual void onActivate(FormHandle deactivateForm); 
            virtual void onDeactivate(FormHandle activateForm) {}
            virtual void onPaint(FormsDisplayHandle display) {}
#ifdef eosFormsService_UseSelector            
            virtual void onSelectorMove(SelectorPosition position, SelectorDirection direction);
            virtual void onSelectorPress();
            virtual void onSelectorRelease();
#endif
#ifdef eosFormsService_UseKeyboard
            virtual void onKeyPress(KeyCode keyCode);
            virtual void onKeyRelease(KeyCode keyCode);
#endif            
            
        friend class FormsService;
    };
}


#endif