#pragma once
#ifndef __eosForm__
#define __eosForm__


#include "eos.h"
#include "Services/Forms/eosControl.h"


namespace eos {

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


#endif // __eosForm__
