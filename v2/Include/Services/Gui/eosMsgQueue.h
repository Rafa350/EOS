#ifndef __eosMsgQueue__
#define __eosMsgQueue__


#include "eos.h"
#include "System/Core/eosQueue.h"


namespace eos {

#if eosGuiService_SelectorEnabled

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

#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled

    enum class KeyCode {
        up,
        down,
        left,
        right,
        accept,
		cancel,
		character
    };

    enum class MsgKeyboardEvent {
        press,
        release
    };

    struct MsgKeyboard {
        MsgKeyboardEvent event;
        KeyCode keyCode;
        char ch;
    };

#endif

#if eosGuiService_TouchPadEnabled

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

    struct MsgCommand {
    	int id;
    	void *param;
    };

    enum class MsgId: uint8_t {
    	null,
    	touchPadEvent,
		selectorEvent,
		keyboardEvent,
		commandEvent
    };

    class Visual;

    struct Message {
        MsgId msgId;
        Visual *target;
        union {
#if eosGuiService_SelectorEnabled
            MsgSelector selector;
#endif
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
            MsgKeyboard keyboard;
#endif
#if eosGuiService_TouchPadEnabled
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
