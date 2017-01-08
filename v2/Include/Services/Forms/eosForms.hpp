#ifndef __EOS_FORMS_HPP
#define __EOS_FORMS_HPP


#include "eos.hpp"
#include "System/Core/eosTask.hpp"
#include "System/Collections/eosList.hpp"
#include "System/Core/eosQueue.hpp"
#include "Controllers/Display/eosDisplay.hpp"
#include "Services/eosService.hpp"
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

    class Application;
    class Form;
    class FormsDisplay;
    class FormsService;


    struct MsgPaint {
        FormsDisplay *display;
    };

#ifdef eosFormsService_UseSelector

    typedef enum class __SelectorEvent {
        inc,
        dec,
        press,
        release
    } SelectorEvent;

    typedef enum class __SelectorDirection {
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

    typedef enum class __KeyCode {
        up,
        down,
        left,
        right,
        enter
    } KeyCode;

    typedef enum class __KeyboardEvent {
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
        Form *target;
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
    
    struct VisualScheme {
        Color labelNormalTextColor;
        Color labelActiveTextColor;
        Color labelDisabledTextColor;
        Color labelBorderColor;
        Color labelBackgroundColor;
        int16_t labelBorderThickness;
        
        Color editorNormalTextColor;
        Color editorActiveTextColor;
        Color editorDisabledTextColor;
        Color editorBorderColor;
        Color editorBackgroundColor;
        int16_t editorBorderThickness;
        
        Color menuBorderColor;
        Color menuSelectedBorderColor;
        Color menuTitleTextColor;
        Color menuTitleBackgroundColor;
        Color menuNormalTextColor;
        Color menuSelectedTextColor;
        Color menuDisabledTextColor;
        Color menuBackgroundColor;
        Color menuSelectedBackgroundColor;
        int16_t menuBorderThickness;
        int16_t menuItemHeight;
    };

    typedef Queue<Message> MessageQueue;

    class FormsService: public Service {
        private:
            typedef List<Form*> FormList;
            typedef ListIterator<Form*> FormListIterator;

        private:
            MessageQueue *messageQueue;
            FormsDisplay *display;
            FormList forms;
            FormList destroyForms;
            Form *activeForm;

        public:
            FormsService(Application *application, MessageQueue *messageQueue, FormsDisplay *display);
            ~FormsService();
            void add(Form *form);
            void remove(Form *form);
            void destroy(Form *form);
            void refresh(Form *form);
            void refresh(Form *form, int16_t x, int16_t y, int16_t width, int16_t height);
            Form *activate(Form *form);
            inline Form *getActiveForm() const { return activeForm; }
        private:
            void run(Task *task);

        friend class Form;
    };

    class FormsDisplay {
        private:
            Display *display;
            uint16_t offsetX;
            uint16_t offsetY;
            uint8_t *buffer;
            uint16_t bufferSize;
            bool wrError;
            uint16_t wrIdx;
            uint16_t rdIdx;            

        public:
            FormsDisplay(Display *display);
            ~FormsDisplay();
            inline Display* getDisplay() const { return display; }
            void beginDraw(int16_t x, int16_t y, int16_t width, int16_t height);
            void endDraw();
            void clear(Color color);
            void setColor(Color color);
            void setTextAlign(HorizontalTextAlign hAlign, VerticalTextAlign vAlign);
            void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
            void drawRectangle(int16_t x, int16_t y, int16_t width, int16_t height, int16_t thickness = 1);
            void drawText(int16_t x, int16_t y, const char *text, int16_t offset, int16_t length);
            void fillRectangle(int16_t x, int16_t y, int16_t width, int16_t height);
            void render();

        private:
            bool wrCheck(uint16_t size);
            void wr8(uint8_t d);
            void wr16(uint16_t d);
            void wr32(uint32_t d);
            void wrs(const char *s);
            void wrEND();
            uint8_t rd8();
            uint16_t rd16();
            uint32_t rd32();
            const char *rds();
    };

    class Form {
        private:
            typedef List<Form*> ChildList;
            typedef ListIterator<Form*> ChildListIterator;
#ifdef eosFormsService_UseKeyboard
            typedef ICallbackP2<Form*, KeyCode> IKeyboardPressEvent;
            typedef ICallbackP2<Form*, KeyCode> IKeyboardReleaseEvent;
#endif
#ifdef eosFormsService_UseSelector
            typedef ICallbackP1<Form*> ISelectorPressEvent;
            typedef ICallbackP1<Form*> ISelectorReleaseEvent;
#endif
        private:
            FormsService* service;
            Form *parent;
            ChildList childs;
#ifdef eosFormsService_UseKeyboard
            IKeyboardPressEvent *evKeyboardPress;
            IKeyboardReleaseEvent *evKeyboardRelease;
#endif
#ifdef eosFormsService_UseSelector
            ISelectorPressEvent *evSelectorPress;
            ISelectorReleaseEvent *evSelectorRelease;
#endif
            int16_t x;
            int16_t y;
            int16_t width;
            int16_t height;
            bool visible;

        public:
            Form(FormsService *service, Form *parent);
            void destroy() { service->destroy(this); }
            void refresh() { service->refresh(this); }
            void refresh(int16_t x, int16_t y, int16_t width, int16_t height) { service->refresh(this, x, y, width, height); }
            void activate() { service->activate(this); }
            void setPosition(int16_t x, int16_t y);
            void setSize(int16_t width, int16_t height);
            void setVisibility(bool visible);
            inline Form *getParent() const { return parent; }
            inline FormsService *getService() const { return service; }
            inline int16_t getX() const { return x; }
            inline int16_t getY() const { return y; }
            inline int16_t getWidth() const { return width; }
            inline int16_t getHeight() const { return height; }
            bool getVisibility() const { return visible; }
            bool isVisible() const;

#ifdef eosFormsService_UseKeyboard
            template <class cls>
            void setKeyboardPressEvent(cls *instance, void (cls::*method)(Form*)) {
                if (evKeyboardPress != nullptr)
                    delete evKeyboardPress;
                evKeyboardPress = new CallbackP2<cls, Form*, KeyCode>(instance, method);
            }

            template <class cls>
            void setKeyboardReleaseEvent(cls *instance, void (cls::*method)(Form*)) {
                if (evKeyboardRelease != nullptr)
                    delete evKeyboardRelease;
                evKeyboardRelease = new CallbackP2<cls, Form*, KeyCode>(instance, method);
            }
#endif
#ifdef eosFormsService_UseSelector
            template <class cls>
            void setSelectorPressEvent(cls *instance, void (cls::*method)(Form*)) {
                if (evSelectorPress != nullptr)
                    delete evSelectorPress;
                evSelectorPress = new CallbackP1<cls, Form*>(instance, method);
            }

            template <class cls>
            void setSelectorReleaseEvent(cls *instance, void (cls::*method)(Form*)) {
                if (evSelectorRelease != nullptr)
                    delete evSelectorRelease;
                evSelectorRelease = new CallbackP1<cls, Form*>(instance, method);
            }
#endif

        protected:
            virtual ~Form();
            virtual void dispatchMessage(const Message &message);
            virtual void onActivate(Form *deactivateForm);
            virtual void onDeactivate(Form *activateForm) {}
            virtual void onPaint(FormsDisplay *display) {}
#ifdef eosFormsService_UseSelector
            virtual void onSelectorMove(SelectorPosition position, SelectorDirection direction);
            virtual void onSelectorPress();
            virtual void onSelectorRelease();
#endif
#ifdef eosFormsService_UseKeyboard
            virtual void onKeyPress(KeyCode keyCode);
            virtual void onKeyRelease(KeyCode keyCode);
#endif
            
        private:
            inline void add(Form *form) { childs.add(form); }
            inline void remove(Form *form) { childs.remove(form); }
            void dispatchPaintMessage(const Message &message);

        friend FormsService;
    };
}


#endif
