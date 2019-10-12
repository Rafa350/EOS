#ifndef __eosButtonBase__
#define __eosButtonBase__


#include "eos.h"
#include "Services/Gui/Visuals/eosContentControl.h"
#include "System/Core/eosCallbacks.h"


namespace eos {

	struct Message;

    class ButtonBase: public ContentControl {
    	private:
			typedef ICallbackP1<Visual*> IClickCallback;

    	private:
			bool pressed;
			IClickCallback *clickCallback;

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
			inline void setClickCallback(CallbackP1<cls, Visual*> *callBack) {
				clickCallback = callBack;
            }
    };

}


#endif // __eosButtonBase__
