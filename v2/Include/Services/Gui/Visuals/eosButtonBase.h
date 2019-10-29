#ifndef __eosButtonBase__
#define __eosButtonBase__


#include "eos.h"
#include "Services/Gui/Visuals/eosContentControl.h"
#include "System/Core/eosCallbacks.h"


namespace eos {

	struct Message;
	class ButtonBase;

	enum class ButtonEventType {
		press,
		release,
		click
	};

	struct ButtonEventArgs {
		ButtonBase *button;
		ButtonEventType event;
		uint8_t id;
	};

    class ButtonBase: public ContentControl {
    	private:
			typedef ICallbackP1<const ButtonEventArgs&> IEventCallback;

    	private:
			bool pressed;
			IEventCallback *eventCallback;

    	protected:
#ifdef OPT_GUI_TouchPad
		    void onTouchPadPress(const Point &position) override;
		    void onTouchPadRelease() override;
		    void onTouchPadLeave() override;
#endif
			virtual void onClick();
			virtual void onPress();
			virtual void onRelease();

			inline bool isPressed() const { return pressed; }

    	public:
			ButtonBase();

			void click();

			template <class cls>
			inline void setEventCallback(CallbackP1<cls, const ButtonEventArgs&> *callback) {
				eventCallback = callback;
            }
    };

}


#endif // __eosButtonBase__
