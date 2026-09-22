module;


#include "eos.h"
#include "eosCallbacks.h"


export module Eos.Services.Forms;


export import Eos.Services.Service;


import Eos.Controllers.Display.Drivers;
import Eos.System.Collections.IntrusiveForwardList;
import Eos.System.Forms.PropertyObserver;
import Eos.System.Graphics;
import Eos.System.Graphics.Color;
import Eos.System.Core.Queue;
import Eos.System.Core.Task;
import Eos.System.Core.Ticks;


export namespace eos {

    class Form;
    class Visual;


    using VisualList = IntrusiveForwardList<Visual, 0>;
    using VisualListNode = IntrusiveForwardListNode<Visual, 0>;


    enum class FormMessageID {
    	selector,
		keyboard,
		activated,
		deactivated,
		initialize
    };

    enum class SelectorMessageID {
    	inc,
		dec,
		press,
		release
    };

    enum class KeyboardMessageID {
    	up,
		down,
		enter,
    };

    struct FormSelectorMessage {
    	SelectorMessageID id;
    };

    struct FormKeyboardMessage {
    	KeyboardMessageID id;
    };

    struct FormMessage {
    	FormMessageID id;
    	Visual *target;
    	union {
    		FormSelectorMessage selector;
    		FormKeyboardMessage keyboard;
    	};
    };


    class FormsService: public Service {
        private:
    		constexpr static const char *_serviceName = "Forms";
    		constexpr static uint32_t _serviceStackDepth = 280;
    		constexpr static Task::Priority _servicePriority = Task::Priority::low;

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
            bool postMessage(FormMessage &message, Ticks blockTime);

            bool postInitializeMessage(Ticks blockTime);
            bool postKeyboardMessage(KeyboardMessageID id, Ticks blockTime);
            bool postSelectorMessage(SelectorMessageID id, Ticks blockTime);

            void setActiveForm(Form *form);
    };


    class Visual: public VisualListNode, public PropertyObserver {
    	private:
    		Point _position;
    		Size _size;
    		Visual *_parent;
    		VisualList _childs;
            bool _renderPending;

    	protected:
            virtual void onMessage(FormMessage &message);
            virtual void onRender(Graphics *graphics);
            virtual void onPropertyChanged(void *property);

    	public:
            Visual(const Point &position, const Size &size);

            inline void setPosition(const Point &value) { setProperty(_position, value); }
            inline void setSize(const Size &value) { setProperty(_size, value); }

            inline Visual* getParent() const { return _parent; }
            Visual *getRoot();
            inline const Point& getPosition() const { return _position; }
            inline const Size& getSize() const { return _size; }

            bool isRenderPending() const;

    		void addChild(Visual *visual);

            void invalidate();
            void message(FormMessage &message);
    		void render(Graphics *graphics);
    };


    class Control: public Visual {
    	public:
    		struct PropertyChangedEventArgs {
    			void *ptr;
    		};
    		using IPropertyChangedEvent = ICallbackP2<Control*, PropertyChangedEventArgs*>;
    		template <typename Instance_> using PropertyChangedEvent = CallbackP2<Instance_, Control*, PropertyChangedEventArgs*>;

        private:
            Color _backgroundColor;
            Color _borderColor;
            IPropertyChangedEvent *_propertyChangedEvent;

        protected:
            void onPropertyChanged(void *property) override;
            void onRender(Graphics *graphics) override;

        public:
            Control(const Point &position, const Size &size);
            Control(const Control &) = delete;
            Control(const Control &&) = delete;

            inline void setBackgroundColor(Color value) { setProperty(_backgroundColor, value); }
            inline void setBorderColor(Color value) { setProperty(_borderColor, value); }

            inline void setPropertyChangedEvent(IPropertyChangedEvent &event) {
            	_propertyChangedEvent = &event;
            }
            inline void clearPropertyChangedEvent() {
            	_propertyChangedEvent = nullptr;
            }

            inline Color getBackgroundColor() const { return _backgroundColor; }
            inline Color getBorderColor() const { return _borderColor; }
    };


    class Form: public Visual {
        private:
            Control *_activeControl;
            void *_dataContext;

        protected:
            void onMessage(FormMessage &message) override;

        public:
            Form();
            Form(void *dataContext);
            Form(const Form &) = delete;
            Form(const Form &&) = delete;

            inline void setDataContext(void *value) { setProperty(_dataContext, value); }
            inline void setActiveControl(Control *value) { setProperty(_activeControl, value); }
            inline void *getDataContext() const { return _dataContext; }
    };

}
