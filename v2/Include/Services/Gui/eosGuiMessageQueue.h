#ifndef __eosGuiMessageQueue__
#define __eosGuiMessageQueue__


#include "eos.h"
#include "System/Core/eosQueue.h"


namespace eos {

#ifdef OPT_GUI_Selector

    enum class MsgSelectorEvent {
        inc,
        dec,
        press,
        release
    };

    struct MsgSelector {
        MsgSelectorEvent event;
        uint16_t delta;
    };

#endif

#ifdef OPT_GUI_Keyboard

    enum class KeyCode {
        up,
        down,
        left,
        right,
        enter
    };

    enum class MsgKeyboardEvent {
        press,
        release
    };

    struct MsgKeyboard {
        MsgKeyboardEvent event;
        KeyCode keyCode;
    };

#endif

#ifdef OPT_GUI_TouchPad

    enum class MsgTouchPadEvent: uint8_t {
    	press,
		release,
		move
    };

    struct MsgTouchPad {
        MsgTouchPadEvent event;
        int x;
        int y;
    };

#endif

    struct Message {
        unsigned id;
        union {
#ifdef OPT_GUI_Selector
            MsgSelector msgSelector;
#endif
#ifdef OPT_GUI_Keyboard
            MsgKeyboard msgKeyboard;
#endif
#ifdef OPT_GUI_TouchPad
            MsgTouchPad msgTouchpad;
#endif
        };
    };

    class GuiMessageQueue {
    	private:
    		Queue<Message> queue;
    	public:
    		GuiMessageQueue();
    		void send(const Message &msg);
    		bool receive(Message &msg);
    };

}


#endif // __eosGuiMessageQueue__