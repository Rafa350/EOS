#ifndef __eosMsgQueue__
#define __eosMsgQueue__


#include "eos.h"
#include "System/eosSingleton.h"
#include "System/Core/eosQueue.h"


namespace eos {

#if eosGuiService_SelectorEnabled

    enum class MsgSelectorEvent: uint8_t {
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

    enum class KeyCode: uint8_t {
        keyUp, keyDown, keyLeft, keyRight,
		keyEnter, keyEsc,
		key0, key1, key2, key3, key4, key5, key6, key7, key8, key9,
		keyA, keyB, keyC, keyD, keyE, keyF, keyG, keyH, keyI, keyJ,
		keyK, keyL, keyM, keyN, keyO, keyP, keyQ, keyR, keyS, keyT,
		keyU, keyV, keyW, keyX, keyY, keyZ
    };

    enum class MsgKeyboardEvent: uint8_t {
        press,
        release
    };

    typedef uint8_t KeyFlags;

    struct MsgKeyboard {
        MsgKeyboardEvent event;
        KeyCode keyCode;
        KeyFlags keyFlags;
    };

#endif

#if eosGuiService_TouchpadEnabled

    enum class MsgTouchpadEvent: uint8_t {
    	press,
		release,
		move,
		enter,
		leave
    };

    struct MsgTouchpad {
        MsgTouchpadEvent event;
        int x;
        int y;
    };

#endif

    struct MsgCommand {
    	int id;
    	void* param;
    };

    enum class MsgId: uint8_t {
    	null,
    	touchpad,
		selector,
		keyboard,
		command,
    };

    class Visual;

    struct Message {
        MsgId msgId;
        Visual* target;
        union {
#if eosGuiService_SelectorEnabled
            MsgSelector selector;
#endif
#if eosGuiService_KeyboardEnabled || eosGuiService_VirtualKeyboardEnabled
            MsgKeyboard keyboard;
#endif
#if eosGuiService_TouchpadEnabled
            MsgTouchpad touchpad;
#endif
            MsgCommand command;
        };
    };

    class MsgQueue {
    	private:
    		Queue<Message> _queue;

    	public:
    		MsgQueue();
    		MsgQueue(const MsgQueue&) = delete;

    		MsgQueue& operator = (const MsgQueue&) = delete;

    		void send(const Message& msg);
    		bool receive(Message& msg);
    		bool isEmpty() const;
    };

    typedef Singleton<MsgQueue> MessageQueue;
}


#endif // __eosGuiMessageQueue__
