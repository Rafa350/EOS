#ifndef __eosMsgQueue__
#define __eosMsgQueue__


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
		move,
		enter,
		leave
    };

    struct MsgTouchPad {
        MsgTouchPadEvent event;
        int x;
        int y;
    };

#endif

    struct MsgKey {
    	int asciiCode;
    };

    struct MsgCommand {
    	int id;
    	void *param;
    };

    enum class MsgId: uint8_t {
    	null,
    	touchPadEvent,
		selectorEvent,
		keyboardEvent,
		commandEvent,
		keyEvent
    };

    class Visual;

    struct Message {
        MsgId msgId;
        Visual *target;
        union {
#ifdef OPT_GUI_Selector
            MsgSelector selector;
#endif
#ifdef OPT_GUI_Keyboard
            MsgKeyboard keyboard;
#endif
#ifdef OPT_GUI_TouchPad
            MsgTouchPad touchPad;
#endif
            MsgCommand command;
        };
    };

    class MsgQueue {
    	private:
    		static MsgQueue *instance;
    		Queue<Message> queue;

    	private:
    		MsgQueue();

    	public:
    		void send(const Message &msg);
    		bool receive(Message &msg);
    		bool isEmpty() const;

    		static MsgQueue *getInstance();
    };

}


#endif // __eosGuiMessageQueue__
