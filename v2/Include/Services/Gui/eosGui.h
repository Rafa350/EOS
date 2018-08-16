#ifndef __eosGui__
#define __eosGui__


// EOS includes
//
#include "eos.h"
#include "Services/eosService.h"
#include "System/Core/eosTask.h"
#include "System/Core/eosQueue.h"


namespace eos {

	class Application;

#ifdef eosFormsService_UseSelector

    enum class SelectorEvent {
        inc,
        dec,
        press,
        release
    };

    typedef struct {
        SelectorEvent event;
        uint16_t delta;
    } MsgSelector;
#endif

#ifdef eosFormsService_UseKeyboard

    enum class KeyCode {
        up,
        down,
        left,
        right,
        enter
    };

    enum class KeyboardEvent {
        press,
        release
    };

    typedef struct {
        KeyboardEvent event;
        KeyCode keyCode;
    } MsgKeyboard;
#endif

#ifdef eosFormsService_UseTouchpad
    typedef struct {
        unsigned event;
    } MsgTouchpad;
#endif

    typedef struct {
        unsigned id;
        //Form *target;
        union {
            //MsgPaint msgPaint;
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
    } Message;

    typedef Queue<Message> MessageQueue;

	typedef struct {
	} GuiServiceInitializeInfo;

	class GuiService: public Service {
		public:
			GuiService(Application *application, const GuiServiceInitializeInfo *pInfo);

		protected:
			void onInitialize();
			void onTask();
	};
}


#endif // __eosGui__

